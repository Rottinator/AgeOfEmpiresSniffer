#ifndef _PARSER_H_
#define _PARSER_H_

#include "../Shared/shared.h"

using namespace AgeOfEmpiresSniffer::Shared;

namespace AgeOfEmpiresSniffer
{
	namespace MapExtractor
	{
		class Parser
		{
		public: 
			Parser();
			GameSettings* GameSettings;
			Map* Map;
			bool Parse(char* filePath);

		private:
			int GetGameSettingsPos(BinaryReader* reader);
			void ReadGameSettings(BinaryReader* reader, int gameSettingsPos);
			int GetTeamIndexPos(BinaryReader* reader);
			void ReadMap(BinaryReader* reader);
			void ReadPlayerInformations(BinaryReader* reader);
			bool FindSequence(BinaryReader* reader, byte* sequence, int sequenceLength, bool searchBackwards);
		};
	}
}

#endif