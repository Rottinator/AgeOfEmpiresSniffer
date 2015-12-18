#ifndef _PLAYER_H_
#define _PLAYER_H_

namespace AgeOfEmpiresSniffer
{
	namespace Shared
	{
		struct Player
		{
			bool IsHuman;
			char* Name;
			int Color;
			int Civilisation;
			int Team;
		};
	}
}

#endif