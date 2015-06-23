#include <cstdio>

#include "../../Base.h/Base.h/io/io.h"

#pragma warning(disable : 4996)

bool Parse(char* filePath)
{
	BinaryReader binaryReader = BinaryReader();
	binaryReader.OpenFile(filePath);

	binaryReader.SetPosition(binaryReader.GetPosition() + 16);

	short unknown1 = binaryReader.ReadShort();
	short stringCount = binaryReader.ReadShort();
	int unknownInt = binaryReader.ReadInteger();
	
	printf("Unknown 1:\t%d\n", unknown1);
	printf("String-Count:\t%d\n", stringCount);
	printf("Unknown Integer:\t%d\n", unknownInt);
	
	for(int i = 0; i < stringCount; i++)
	{
		int stringLength = binaryReader.ReadInteger();
		int position = binaryReader.GetPosition();
		position += stringLength;
		binaryReader.SetPosition(position);
	}

	int position = binaryReader.GetPosition();
	printf("Position After String-Read: %d\n", position);



	binaryReader.CloseFile();
	
	return true;
}