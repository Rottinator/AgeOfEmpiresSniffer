#include <cstdio>
#include <cstdlib>

#include "../../Base.h/Base.h/io/io.h"

#include "RecordReader.h"

#define FILENAME "D:\\Steam\\SteamApps\\common\\Age2HD\\savegame\\MP Replay v4.2 @2015.07.09 212519 (1).msx2"
//#define FILENAME "D:\\Steam\\SteamApps\\common\\Age2HD\\savegame\\MP Replay v4.2 @2015.07.02 190223 (1).msx2"

int main() 
{
	RecordReader recordReader = RecordReader();

	recordReader.ReadRecordFile(FILENAME, true);

	system("PAUSE");

	return 0;
}
