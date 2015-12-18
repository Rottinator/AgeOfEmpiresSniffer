#ifndef _MAP_H_
#define _MAP_H_

#include "player.h"
#include "../../../Base.h/Base/base.h"

namespace AgeOfEmpiresSniffer
{
	namespace Shared
	{
		struct Map
		{
			byte* TerrainPoints;
			int TerrainPointsLength;
		};
	}
}

#endif