#include <cstdio>
#include <cstdlib>

#include "..\..\Base.h\Base.h\compression\compression.h"

int main()
{
	char inputPath[255] = "C:\\Program Files (x86)\\Steam\\SteamApps\\common\\Age2HD\\Scenario\\SnifferEmptyMiddleSize.scx2";
	char outputPath[255] = "D:\\output\\aoe2maps\\scenario.sc";

	FILE* inputFile = fopen(inputPath, "rb");
	FILE* outputFile = fopen(outputPath, "wb");

	fseek(inputFile, 0, SEEK_END);
	int fileSize = ftell(inputFile);
	fseek(inputFile, 28, SEEK_SET);

	FileInflate fileInflate;
	fileInflate.CompressionMode = DeflateCompressionMode::Default;
	fileInflate.Input = inputFile;
	fileInflate.Output = outputFile;
	fileInflate.Size = fileSize - 28;

	int result = fileInflate.Decompress();

	fclose(inputFile);
	fclose(outputFile);

	if(result == INFLATE_ERROR)
	{
		printf("Fehler beim Entpacken des Szenarios\n");
	}
	else
	{
		printf("Szenario erfolgreich entpackt\n");
	}
	
	system("PAUSE");
	return 0;
}