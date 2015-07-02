#include "../../Base.h/Base.h/io/io.h"

class ActionHandler
{
private:
	BinaryReaderBase* _reader;


public:
	ActionHandler(BinaryReaderBase* reader)
	{
		_reader = reader;
	}

	void ReadAndHandleAction()
	{
		int packetSize = _reader->ReadInteger();
		int packetId = _reader->ReadInteger();
		int position = _reader->GetPosition();

		printf("Packet Received: 0x%08X Size: %d Position: %d\n", packetId, packetSize, position);
		_reader->SetPosition(position + packetSize);
	}

private:

};