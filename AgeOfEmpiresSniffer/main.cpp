#include <cstdio>
#include <cstdlib>

#include "../../Base.h/Base.h/io/io.h"

#define FILENAME "D:\\Steam\\SteamApps\\common\\Age2HD\\savegame\\recorded game -  25-Mai-2015 14`56`28.mgx2"
//#define FILENAME "D:\\Steam\\SteamApps\\common\\Age2HD\\savegame\\recorded game -  22-Mai-2015 18`02`24.mgx2"

BinaryReader reader;

void ReadAndPrintInteger(int count, int position);

void HandleCameraMovement()
{
	int randomNumber = reader.ReadInteger();
	int actionId = reader.ReadInteger();

	if (actionId == 0)
	{
		reader.SetPosition(reader.GetPosition() + 7 * 4);
	}
	
	float xCoord = reader.ReadFloat();
	float yCoord = reader.ReadFloat();

	randomNumber = reader.ReadInteger();
}

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

void HandlePacket()
{
	int packetSize = reader.ReadInteger();
	int packetId = reader.ReadInteger();

	switch (packetId)
	{
		case 256:
			ReadCollection();
			break;
		case 259:
			ReadMovement();
			break;
		default:
			int position = reader.GetPosition();
			printf("Unknown Packet: %d at Position: %d\n", packetId, position);
			reader.SetPosition(position + packetSize);
			break;
	}
}

void DoIt()
{
	int jumpCount = reader.ReadInteger();

	reader.SetPosition(jumpCount);

	printf("Starting at position %d\n", jumpCount);

	int actionId = -1;
	actionId = reader.ReadInteger();

	while (reader.LastReadedCount > 0)
	{
		int pos = reader.GetPosition();
		
		switch (actionId)
		{
		case 1:
			HandlePacket();
			break;
		case 2: 
			HandleCameraMovement();
			break;
		case 4: 
			printf("First command\n");
			reader.SetPosition(pos + (6 * 4));
			break;
		default: 
			//printf("Unknown action %d\n", actionId);
			break;
		}

		actionId = reader.ReadInteger();
	}

	int pos = reader.GetPosition();

	printf("Finished at position %d\n", pos);
}


int main() 
{
	reader = BinaryReader();
	reader.OpenFile(FILENAME);

	DoIt();
	
	/*ReadAndPrintInteger(7, 191913 - 6*4);
	ReadAndPrintInteger(7, 191913);
	ReadAndPrintInteger(6, 191913 + 7*4);*/

	//ReadAndPrintInteger(6 + 3, 188229 - 8);
	//ReadAndPrintInteger(5 + 3, 191289 - 8);
	//ReadAndPrintInteger(7 + 3, 200277 - 8);
	//ReadAndPrintInteger(6 + 3, 205841 - 8);
	//ReadAndPrintInteger(5 + 3, 219825 - 8);
	//ReadAndPrintInteger(5 + 3, 222881 - 8);
	//ReadAndPrintInteger(6 + 3, 226513 - 8);
	//ReadAndPrintInteger(5 + 3, 235817 - 8);
	//ReadAndPrintInteger(6 + 3, 239137 - 8);
	//ReadAndPrintInteger(5 + 3, 244193 - 8);
	//ReadAndPrintInteger(5 + 3, 249049 - 8);
	//ReadAndPrintInteger(5 + 3, 251289 - 8);
	//ReadAndPrintInteger(5 + 3, 258957 - 8);
	//ReadAndPrintInteger(5 + 3, 267201 - 8);
	//ReadAndPrintInteger(5 + 3, 272537 - 8);

	reader.CloseFile();

	system("PAUSE");

	return 0;
}

void ReadAndPrintInteger(int count, int position)
{
	reader.SetPosition(position);

	for (int i = 0; i < count; i++) 
	{
		int number = reader.ReadInteger();

		if (i == 0 && number == 256)
			return;

		printf("%d ", number);
	}

	printf(" Pos: %d\n", reader.GetPosition());
}