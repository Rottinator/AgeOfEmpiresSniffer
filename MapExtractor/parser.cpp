#include "../../Base.h/Base/base.h"
#include "../Shared/shared.h"
#include "parser.h"

using namespace Base::IO;
using namespace AgeOfEmpiresSniffer::Shared;

byte GAME_SETTINGS_SEQUENCE[4] = { 0x9D, 0xFF, 0xFF, 0xFF };
byte TEAM_INDEX_SEQUENCE[8] = { 0x9A, 0x99, 0x99, 0x99, 0x99, 0x99, 0xF9, 0x3F };

namespace AgeOfEmpiresSniffer
{
	namespace MapExtractor
	{
		Parser::Parser()
		{
			this->Map = new struct Map;
			this->GameSettings = new struct GameSettings;
			this->GameSettings->PlayerCount = 0;
		}

		bool Parser::Parse(char* filePath)
		{
			BinaryReader* binaryReader = new BinaryReader();
			binaryReader->OpenFile(filePath);

			int teamIndexPos = GetTeamIndexPos(binaryReader);

			int gameSettingsPos = GetGameSettingsPos(binaryReader);

			this->ReadGameSettings(binaryReader, gameSettingsPos);

			this->ReadMap(binaryReader);

			this->ReadPlayerInformations(binaryReader);

			binaryReader->CloseFile();

			return true;
		}
	
		void Parser::ReadMap(BinaryReader* reader)
		{
			reader->SetPosition(126);

			int width = reader->ReadInteger();
			int height = reader->ReadInteger();

			printf("width: %d heigth: %d\n", width, height);

			//8 Byte überspringen, erstes Byte meistens nur ne 7 und 2. Byte das Resultat aus Breite*Höhe
			reader->SetPosition(8, SEEK_CUR);

			//Die statischen 15600, kp woher die kommen, war bisher bei allen files so und dann irgendwie 14 Byte pro koordinate (alles aber irgendwie nur 0en o.O)
			reader->SetPosition(15600 + (width*height * 14), SEEK_CUR);

			//Dann kommt irgendwie son Byte und wenn man bei dem das mal 4 nimmt, kommt man fast direkt beim Anfang des Terrains raus
			//Kann auch sein, dass das nix damit zu tun hat :O
			int jumpCount = reader->ReadInteger();
			reader->SetPosition(jumpCount * 4, SEEK_CUR);

			//Und nochmal 4 weiter da steht immer nur ne dämliche 1
			reader->SetPosition(6, SEEK_CUR);
			
			int count = width * height;

			byte* terrain = new byte[count];

			for (int i = 0; i < count; i++)
			{
				byte textureId = reader->ReadUChar();
				terrain[i] = textureId;
				byte unknown = reader->ReadUChar();
			}

			printf("Position after terrain: %d\n", reader->GetPosition());

			int dataCount = reader->ReadInteger();
			reader->SetPosition(4, SEEK_CUR);
			reader->SetPosition(4 * dataCount, SEEK_CUR);

			for (int i = 0; i < dataCount; i++)
			{
				int couples = reader->ReadInteger();
				reader->SetPosition(8 * couples, SEEK_CUR);
			}

			int width2 = reader->ReadInteger();
			int height2 = reader->ReadInteger();

			printf("width2: %d height2: %d\n", width2, height2);

			reader->SetPosition(width2*height2 * 4, SEEK_CUR);

			printf("Position after jump: %d\n", reader->GetPosition());
		}

		int Parser::GetGameSettingsPos(BinaryReader* reader)
		{
			int sequenceSize = sizeof(GAME_SETTINGS_SEQUENCE);
			reader->SetPosition(-sequenceSize, SEEK_CUR);

			bool found = this->FindSequence(reader, (byte*)GAME_SETTINGS_SEQUENCE, sequenceSize, true);

			if (found)
			{
				int position = reader->GetPosition();
				printf("Game-Settings-Position: %d\n", position);
				return position;
			}
			else
			{
				printf("Game-Settings-Position konnte nicht gefunden werden\n");
				return -1;
			}
		}

		void Parser::ReadGameSettings(BinaryReader* reader, int gameSettingsPos)
		{
			//8 Überspringen, weil da nur Bullshit kommt
			int readPos = gameSettingsPos + sizeof(GAME_SETTINGS_SEQUENCE) + 8;

			reader->SetPosition(readPos);

			int mapId = reader->ReadInteger();
			int difficulty = reader->ReadInteger();
			int lockTeams = reader->ReadInteger();

			printf("MapId: %d Difficulty: %d, lockTeams: %d\n", mapId, difficulty, lockTeams);

			reader->SetPosition(16, SEEK_CUR);

			Player** players = new Player*[9]; //9 Stück, weil der erste Spieler immer der aufnehmende ist + max 8 Spieler

			for (int i = 0; i < 9; i++)
			{
				int playerIndex = reader->ReadInteger();
				int human = reader->ReadInteger();
				int nameLength = reader->ReadInteger();

				if (playerIndex == 0 && nameLength == 0)
				{
					break;
				}

				Player* player = new Player;
				players[playerIndex] = player;
				player->IsHuman = human == 2;
				player->Name = (char*)malloc(nameLength + 1);

				for (int n = 0; n < nameLength; n++)
				{
					player->Name[n] = reader->ReadChar();
				}

				player->Name[nameLength] = 0; //String-Ende Byte

				if (playerIndex > 0)
				{
					this->GameSettings->PlayerCount++;
				}

				printf("Player %d %s\n", playerIndex, player->Name);
			}

			this->GameSettings->Players = players;
		}

		int Parser::GetTeamIndexPos(BinaryReader* reader)
		{
			int sequenceSize = sizeof(TEAM_INDEX_SEQUENCE);
			reader->SetPosition(-sequenceSize, SEEK_END);

			bool found = this->FindSequence(reader, (byte*)TEAM_INDEX_SEQUENCE, sequenceSize, true);

			if (found)
			{
				int position = reader->GetPosition();
				printf("Team-Index-Position: %d\n", position);
				return position;
			}
			else
			{
				printf("Team-Index-Position konnte nicht gefunden werden\n");
				return -1;
			}
		}

		void Parser::ReadPlayerInformations(BinaryReader* reader)
		{
			for (int i = 0; i < this->GameSettings->PlayerCount; i++)
			{
				Player* player = this->GameSettings->Players[i+1]; //weil an index 0 immer der aufnehmende spieler steht, also ein 2. mal
				int nameLength = strlen(player->Name);

				bool found = this->FindSequence(reader, (byte*)player->Name, nameLength, false);

				if (found) 
				{
					reader->SetPosition(817, SEEK_CUR);
					player->Civilisation = reader->ReadUChar();
					reader->SetPosition(3, SEEK_CUR);
					player->Color = reader->ReadUChar();

					printf("%s : %d %d\n", player->Name, player->Civilisation, player->Color);
				}
				else
				{
					printf("Spieler %s konnte nicht gefunden werden\n", player->Name);
					break;
				}
			}
		}

		bool Parser::FindSequence(BinaryReader* reader, byte* sequence, int sequenceLength, bool searchBackwards)
		{
			byte* bytes = new byte[sequenceLength];
			bool firstRun = true;

			do {
				if (firstRun)
				{
					reader->Read((void*)bytes, sequenceLength);
					firstRun = false;
				}
				else
				{
					if (searchBackwards)
					{
						for (int i = sequenceLength - 2; i > 0; i--)
						{
							bytes[i + 1] = bytes[i];
						}

						reader->SetPosition(-2, SEEK_CUR);

						bytes[0] = reader->ReadUChar();
					}
					else
					{
						for (int i = 1; i < sequenceLength; i++)
						{
							bytes[i - 1] = bytes[i];
						}

						bytes[sequenceLength - 1] = reader->ReadUChar();
					}
				}

				if (reader->LastReadedCount == 0)
				{
					delete bytes;
					return false;
				}
			} while (ArrayUtils::CompareByteArrays(bytes, sequence, sequenceLength) == false);

			delete bytes;
			return true;
		}
	}
}
