#include <cstdio>
#include <string>
#include <cstdlib>

#include "extractor.h"
#include "parser.h"

#define INPUT_PATH "C:\\Program Files (x86)\\Steam\\SteamApps\\common\\Age2HD\\savegame\\recorded game -  09-Jun-2015 13`30`46.mgx2"
#define OUTPUT_PATH "D:\\output\\aoe2maps\\steppe2.map"

int main() 
{
	bool extractionResult = Extract(INPUT_PATH, OUTPUT_PATH);
	
	if(extractionResult == false)
	{
		system("Pause");
		return 0;
	}

	char path1[255] = "D:\\output\\aoe2maps\\1.map";
	char path2[255] = "D:\\output\\aoe2maps\\steppe2.map";

	printf("\nFile 1:\n\n");
	Parse(path1);

	printf("\nFile 2:\n\n");
	Parse(path2);

	system("Pause");

	return 0;
}