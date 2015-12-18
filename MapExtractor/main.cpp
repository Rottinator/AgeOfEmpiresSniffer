#include <cstdio>
#include <string>
#include <cstdlib>

#include "extractor.h"
#include "parser.h"

//#define INPUT_PATH "D:\\SteamLibrary\\SteamApps\\common\\Age2HD\\savegame\\MP Replay v4.3 @2015.09.14 210940 (1).msx2"
#define INPUT_PATH "D:\\SteamLibrary\\SteamApps\\common\\Age2HD\\savegame\\MP Replay v4.3 @2015.10.20 212838 (1).msx2"
//#define INPUT_PATH "D:\\Steam\\SteamApps\\common\\Age2HD\\savegame\\MP Replay v4.2 @2015.07.09 212519 (1).msx2"

#define OUTPUT_PATH "C:\\Temp\\multi3.map"

using namespace AgeOfEmpiresSniffer::MapExtractor;

int main()
{
	Extractor extractor;
	bool extractionResult = extractor.Extract(INPUT_PATH, OUTPUT_PATH);

	if (extractionResult == false)
	{
		system("Pause");
		return 0;
	}
	else
	{
		Parser parser;
		parser.Parse(OUTPUT_PATH);
	}

	system("Pause");

	return 0;
}