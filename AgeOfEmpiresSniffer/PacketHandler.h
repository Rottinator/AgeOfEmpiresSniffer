#include "../../Base.h/Base.h/io/io.h"

#include "ActionHandler.h"

class PacketHandler
{
private:
	BinaryReaderBase* _reader;
	ActionHandler* _actionHandler;

public:
	PacketHandler(BinaryReaderBase* reader)
	{
		_reader = reader;
		_actionHandler = new ActionHandler(reader);
	}

	void HandlePacket(int packetId)
	{
		switch (packetId)
		{
		case 1:
			_actionHandler->ReadAndHandleAction();
			break;
		case 2:
			HandleCameraPacket();
			break;
		case 4:
			HandleStartCommand();
			break;
		default:
			printf("Unknown packet %d\n", packetId);
			break;
		}
	}

private:
	void HandleCameraPacket()
	{
		int randomNumber = _reader->ReadInteger();
		int actionId = _reader->ReadInteger();

		if (actionId == 0)
		{
			_reader->SetPosition(_reader->GetPosition() + 7 * 4);
		}

		float xCoord = _reader->ReadFloat();
		float yCoord = _reader->ReadFloat();

		randomNumber = _reader->ReadInteger();
	}

	void HandleStartCommand()
	{
		int pos = _reader->GetPosition();
		printf("Start Command\n");
		_reader->SetPosition(pos + (6 * 4));
	}
};