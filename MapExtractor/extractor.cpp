#include <cstdio>
#include "../../Base.h/Base/base.h"

#include "extractor.h"

using namespace Base::Compression;

namespace AgeOfEmpiresSniffer
{
	namespace MapExtractor
	{
		bool Extractor::Extract(char* inputPath, char* outputPath)
		{
			FILE* inFile = fopen(inputPath, "rb");
			if (inFile == NULL)
			{
				printf("Input File konnte nicht geöffnet werden!\n");
				return false;
			}

			FILE* outFile = fopen(outputPath, "wb");
			if (outFile == NULL)
			{
				printf("Output File konnte nicht geöffnet werden!\n");
				return false;
			}

			int readPoint = 0;
			fread(&readPoint, sizeof(int), 1, inFile);
			fseek(inFile, 8, SEEK_SET);

			FileInflate fileInflate;
			fileInflate.CompressionMode = DeflateCompressionMode::Default;
			fileInflate.Input = inFile;
			fileInflate.Output = outFile;
			fileInflate.Size = readPoint - 8;

			int result = fileInflate.Decompress();

			fclose(inFile);
			fclose(outFile);

			if (result == INFLATE_SUCCESS)
			{
				printf("Datei erfolgreich dekomprimiert\n");
				return true;
			}
			else if (result == INFLATE_ERROR)
			{
				printf("Fehler beim Dekomprimieren der Datei\n");
				return false;
			}

			return true;
		}
	}
}