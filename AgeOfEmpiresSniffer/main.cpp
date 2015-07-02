#include <cstdio>
#include <cstdlib>

#include "../../Base.h/Base.h/io/io.h"

#include "RecordReader.h"

//#define FILENAME "D:\\Steam\\SteamApps\\common\\Age2HD\\savegame\\SP Replay v4.2 @2015.07.01 182104.mgx2"
#define FILENAME "D:\\Steam\\SteamApps\\common\\Age2HD\\savegame\\MP Replay v4.2 @2015.07.02 190223 (1).msx2"

ExpandoBinaryReader reader = ExpandoBinaryReader(10);

void ReadCollection()
{
	int objectId = reader.ReadInteger();
	int unitCount = reader.ReadInteger();
	float xCoord = reader.ReadFloat();
	float yCoord = reader.ReadFloat();

	printf("Collecting Object %d on Coords x: %.2f y: %.2f ", objectId, xCoord, yCoord);

	if (unitCount < 255 && unitCount > 0)
	{
		printf("with units [");
		for (int i = 0; i < unitCount; i++)
		{
			int unitId = reader.ReadInteger();

			printf("%d, ", unitId);
		}

		printf("]");
	}
	else
	{
		printf("with last selected units");
	}

	int timestamp = reader.ReadInteger();

	printf("\n");
	printf("Position: %d\n", reader.GetPosition());
}

void ReadMovement()
{
	int randomNumber = reader.ReadInteger();
	int unitCount = reader.ReadInteger();
	float xCoord = reader.ReadFloat();
	float yCoord = reader.ReadFloat();

	printf("Moving units on Coords x:%.2f y: %.2f ", xCoord, yCoord);

	if (unitCount < 255 && unitCount > 0)
	{
		printf(" [");
		for (int i = 0; i < unitCount; i++)
		{
			int unitId = reader.ReadInteger();

			printf("%d, ", unitId);
		}

		printf("]");
	}
	else
	{
		printf("of last selection");
	}

	int timestamp = reader.ReadInteger();

	printf("\n");
}

int main() 
{
	RecordReader recordReader = RecordReader();

	recordReader.ReadRecordFile(FILENAME, true);


	//reader.OpenFile(FILENAME);

	//DoIt();

	//reader.CloseFile();

	system("PAUSE");

	return 0;
}
