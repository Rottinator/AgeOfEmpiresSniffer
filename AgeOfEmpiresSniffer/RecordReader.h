#include "PacketHandler.h"

class RecordReader
{
private:
	BinaryReaderBase* _reader;
	PacketHandler* _packetHandler;

public:
	void ReadRecordFile(char* path, bool isLiveFile);

private:
	void ParseFile(bool isLiveFile);
	bool CreateBinaryReader(char* path, bool isLiveFile);
};