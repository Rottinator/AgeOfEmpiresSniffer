#ifndef _GAME_SETTINGS_H_
#define _GAME_SETTINGS_H_

#include "player.h"

namespace AgeOfEmpiresSniffer
{
	namespace Shared
	{
		struct GameSettings
		{
			int MapId;
			int Difficulty;
			bool LockTeams;
			Player** Players;
			int PlayerCount;
		};
	}
}

#endif