#include "../../Base.h/Base/base.h"

using namespace Base::IO;

struct Action
{
	byte Id;
	byte Size;
	byte Info1;
	byte Info2;
	byte Info3;
};

class ActionHandler
{
private:
	BinaryReaderBase* _reader;

public:
	ActionHandler(BinaryReaderBase* reader);
	void ReadAndHandleAction();

private:
	void ReadUnitInteraction(Action action);
	void ReadMovement(Action action);
	void ReadSetOutput(Action action);
	void ReadBuilding(Action action);
	void ReadRecruitment(Action action);
	void ReadResearch(Action action);
	void ReadAndPrintIntegers(int count);
};