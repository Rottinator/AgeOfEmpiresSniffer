#include "ActionHandler.h"

class PacketHandler
{
private:
	BinaryReaderBase* _reader;
	ActionHandler* _actionHandler;

public:
	PacketHandler(BinaryReaderBase* reader);
	void HandlePacket(int packetId);

private:
	float lastX;
	float lastY;

	void HandleCameraPacket();
	void HandleStartCommand();
};