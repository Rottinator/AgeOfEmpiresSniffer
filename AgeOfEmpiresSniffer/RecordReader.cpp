#include "../../Base.h/Base/base.h"
#include "RecordReader.h"

using namespace Base::IO;

void RecordReader::ReadRecordFile(char* path, bool isLiveFile)
{
	if (CreateBinaryReader(path, isLiveFile) == false)
	{
		return;
	}

	_packetHandler = new PacketHandler(_reader);

	ParseFile(isLiveFile);
}

void RecordReader::ParseFile(bool isLiveFile)
{
	int jumpCount = _reader->ReadInteger();

	_reader->SetPosition(jumpCount);

	printf("RecordReader - Start at Position: %d\n", jumpCount);

	int packetId = -1;
	packetId = _reader->ReadInteger();

	if (isLiveFile == true)
	{
		while (true)
		{
			_packetHandler->HandlePacket(packetId);
			packetId = _reader->ReadInteger();
		}
	}
	else
	{
		BinaryReader* binaryReader = (BinaryReader*)(_reader);

		while (binaryReader->LastReadedCount > 0)
		{
			_packetHandler->HandlePacket(packetId);
			packetId = _reader->ReadInteger();
		}
	}
}

bool RecordReader::CreateBinaryReader(char* path, bool isLiveFile)
{
	if (isLiveFile == true)
	{
		ExpandoBinaryReader* expandoBinaryReader = new ExpandoBinaryReader(10);

		_reader = (BinaryReaderBase*)expandoBinaryReader;
	}
	else
	{
		BinaryReader* binaryReader = new BinaryReader();

		_reader = (BinaryReaderBase*)binaryReader;
	}

	bool success = _reader->OpenFile(path);

	if (success == false)
	{
		printf("Can't open file: %s\n", path);
		return false;
	}

	return true;
}
