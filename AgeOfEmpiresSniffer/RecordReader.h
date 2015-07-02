#include "../../Base.h/Base.h/io/io.h"

#include "PacketHandler.h"

class RecordReader
{
private:
	BinaryReaderBase* _reader;
	PacketHandler* _packetHandler;

public:
	void ReadRecordFile(char* path, bool isLiveFile)
	{
		if (CreateBinaryReader(path, isLiveFile) == false)
		{
			return;
		}

		_packetHandler = new PacketHandler(_reader);

		ParseFile(isLiveFile);
	}

private:
	void ParseFile(bool isLiveFile)
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
	
	bool CreateBinaryReader(char* path, bool isLiveFile)
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
};