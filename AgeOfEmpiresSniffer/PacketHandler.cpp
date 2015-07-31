#include "../../Base.h/Base/base.h"
#include "PacketHandler.h"

using namespace Base::IO;

PacketHandler::PacketHandler(BinaryReaderBase* reader)
{
	_reader = reader;
	_actionHandler = new ActionHandler(reader);
}

void PacketHandler::HandlePacket(int packetId)
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

void PacketHandler::HandleCameraPacket()
{
	int randomNumber = _reader->ReadInteger();
	int actionId = _reader->ReadInteger();

	if (actionId == 0)
	{
		_reader->SetPosition(_reader->GetPosition() + 7 * 4);
	}

	float xCoord = _reader->ReadFloat();
	float yCoord = _reader->ReadFloat();

	if (xCoord != lastX || yCoord != lastY)
	{
		//printf("Camera x: %.2f y: %.2f | randomNumber: %d actionId: %d\n", xCoord, yCoord, randomNumber, actionId);
		lastX = xCoord;
		lastY = yCoord;
	}

	randomNumber = _reader->ReadInteger();
}

void PacketHandler::HandleStartCommand()
{
	printf("Start Command\n");

	int packet = _reader->ReadInteger();

	if (packet == 500)
	{
		int pos = _reader->GetPosition();
		_reader->SetPosition(pos + (5 * 4));
	}
	else if (packet == -1)
	{
		int stringLength = _reader->ReadInteger();
		int pos = _reader->GetPosition();
		_reader->SetPosition(pos + stringLength);
	}
}