#include "../../Base.h/Base/base.h"
#include "parser.h"

using namespace Base::IO;

int GetGameSettingsPos(BinaryReader reader);
void ReadStrings(BinaryReader binaryReader);
bool CompareWithGameSettingsSequence(byte byteArray[]);
void ReadGameSettings(BinaryReader reader, int gameSettingsPos);
void ReadMap(BinaryReader reader);

byte GAME_SETTINGS_SEQUENCE[4] = { 0x9D, 0xFF, 0xFF, 0xFF };


bool Parse(char* filePath)
{
	BinaryReader binaryReader = BinaryReader();
	binaryReader.OpenFile(filePath);

	ReadMap(binaryReader);

	int gameSettingsPos = GetGameSettingsPos(binaryReader);

	ReadGameSettings(binaryReader, gameSettingsPos);

	binaryReader.CloseFile();

	return true;
}

void ReadMap(BinaryReader reader)
{
	reader.SetPosition(126);

	int width = reader.ReadInteger();
	int height = reader.ReadInteger();

	printf("width: %d heigth: %d\n", width, height);

	//8 Byte überspringen, erstes Byte meistens nur ne 7 und 2. Byte das Resultat aus Breite*Höhe
	reader.SetPosition(8, SEEK_CUR);

	//Die statischen 15600, kp woher die kommen, war bisher bei allen files so und dann irgendwie 14 Byte pro koordinate (alles aber irgendwie nur 0en o.O)
	reader.SetPosition(15600 + (width*height * 14), SEEK_CUR);

	//Dann kommt irgendwie son Byte und wenn man bei dem das mal 4 nimmt, kommt man fast direkt beim Anfang des Terrains raus
	//Kann auch sein, dass das nix damit zu tun hat :O
	int jumpCount = reader.ReadInteger();
	reader.SetPosition(jumpCount * 4, SEEK_CUR);

	//Und nochmal 4 weiter da steht immer nur ne dämliche 1
	reader.SetPosition(6, SEEK_CUR);

	FILE* writeFile = fopen("C:\\temp\\outfile.bt", "w");

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			byte textureId = reader.ReadUChar();
			byte unknown = reader.ReadUChar();

			fwrite(&textureId, sizeof(textureId), 1, writeFile);
		}
	}

	fclose(writeFile);

	printf("Position after terrain: %d\n", reader.GetPosition());

	int dataCount = reader.ReadInteger();
	reader.SetPosition(4, SEEK_CUR);
	reader.SetPosition(4 * dataCount, SEEK_CUR);

	for (int i = 0; i < dataCount; i++)
	{
		int couples = reader.ReadInteger();
		reader.SetPosition(8 * couples, SEEK_CUR);
	}

	int width2 = reader.ReadInteger();
	int height2 = reader.ReadInteger();

	printf("width2: %d height2: %d\n", width2, height2);

	reader.SetPosition(width2*height2 * 4, SEEK_CUR);

	printf("Position after jump: %d\n", reader.GetPosition());
}


int GetGameSettingsPos(BinaryReader reader)
{
	int sequenceSize = sizeof(GAME_SETTINGS_SEQUENCE);
	int position = 0;

	reader.SetPosition(-sequenceSize, SEEK_END);

	byte bytes[4];

	do {

		for (int i = 0; i < sequenceSize; i++)
		{
			bytes[i] = reader.ReadUChar();
		}

		position = reader.GetPosition() - sequenceSize;

		reader.SetPosition(position - 1);

	} while (CompareWithGameSettingsSequence(bytes) == false);

	printf("Game-Settings-Position: %d\n", position);

	return position;
}

void ReadGameSettings(BinaryReader reader, int gameSettingsPos)
{
	//8 Überspringen, weil da nur Bullshit kommt
	int readPos = gameSettingsPos + sizeof(GAME_SETTINGS_SEQUENCE) + 8;

	reader.SetPosition(readPos);

	int mapId = reader.ReadInteger();
	int difficulty = reader.ReadInteger();
	int lockTeams = reader.ReadInteger();

	printf("MapId: %d Difficulty: %d, lockTeams: %d\n", mapId, difficulty, lockTeams);

	reader.SetPosition(16, SEEK_CUR);

	Player players[9];

	for (int i = 0; i < 9; i++)
	{
		int playerIndex = reader.ReadInteger();
		int human = reader.ReadInteger();
		int nameLength = reader.ReadInteger();

		if (playerIndex == 0 && nameLength == 0)
		{
			break;
		}

		Player player = players[playerIndex];
		player.isHuman = human == 2;
		player.nameLength = nameLength;
		player.name = (char*)malloc(nameLength + 1);

		for (int n = 0; n < nameLength; n++)
		{
			player.name[n] = reader.ReadChar();
		}

		player.name[nameLength] = 0;

		printf("Player %d %s\n", playerIndex, player.name);
	}
}

bool CompareWithGameSettingsSequence(byte byteArray[])
{
	for (int i = 0; i < 4; i++)
	{
		if (GAME_SETTINGS_SEQUENCE[i] != byteArray[i])
		{
			return false;
		}
	}

	return true;
}

void ReadStrings(BinaryReader binaryReader)
{
	binaryReader.SetPosition(16);

	short unknown1 = binaryReader.ReadShort();
	short stringCount = binaryReader.ReadShort();
	int unknownInt = binaryReader.ReadInteger();

	printf("Unknown 1:\t%d\n", unknown1);
	printf("String-Count:\t%d\n", stringCount);
	printf("Unknown Integer:\t%d\n", unknownInt);

	for (int i = 0; i < stringCount; i++)
	{
		int stringLength = binaryReader.ReadInteger();
		int position = binaryReader.GetPosition();
		position += stringLength;
		binaryReader.SetPosition(position);
	}

	binaryReader.SetPosition(6, SEEK_CUR);

	for (int i = 0; i < 8; i++)
	{
		binaryReader.SetPosition(10, SEEK_CUR);
		short numRule = binaryReader.ReadShort();
		binaryReader.SetPosition(4, SEEK_CUR);
		binaryReader.SetPosition(400 * numRule, SEEK_CUR);
	}

	binaryReader.SetPosition(5544, SEEK_CUR);

	int position = binaryReader.GetPosition();


	printf("Position After String-Read: %d\n", position);
}
