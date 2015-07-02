#include <cstdio>
#include <string>
#include <cstdlib>

#include "extractor.h"
#include "parser.h"

#define INPUT_PATH "D:\\Steam\\SteamApps\\common\\Age2HD\\savegame\\ES Wiederholung v4.1 @2015.06.25 211733.mgx2"

#define OUTPUT_PATH "D:\\Temp\\scenario_empty.map"

int main() 
{
	bool extractionResult = Extract(INPUT_PATH, OUTPUT_PATH);
	
	if(extractionResult == false)
	{
		system("Pause");
		return 0;
	}

	/*char path1[255] = "D:\\output\\aoe2maps\\1.map";
	char path2[255] = "D:\\output\\aoe2maps\\steppe2.map";

	printf("\nFile 1:\n\n");
	Parse(path1);

	printf("\nFile 2:\n\n");
	Parse(path2);*/

	system("Pause");

	return 0;
}