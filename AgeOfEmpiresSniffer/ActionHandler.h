#include "../../Base.h/Base.h/io/io.h"

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
	ActionHandler(BinaryReaderBase* reader)
	{
		_reader = reader;
	}

	void ReadAndHandleAction()
	{
		Action action;

		action.Size = _reader->ReadInteger();
	
		action.Id = _reader->ReadUChar();
		action.Info1 = _reader->ReadUChar();
		action.Info2 = _reader->ReadUChar();
		action.Info3 = _reader->ReadUChar();

		int firstPosition = _reader->GetPosition();

		switch (action.Id)
		{
			case 0x00:
				ReadUnitInteraction(action);
				break;
			case 0x03:
				ReadMovement(action);
				break;
			case 0x65:
				ReadResearch(action);
				break;
			case 0x66:
				ReadBuilding(action);
				break;
			case 0x77:
				ReadRecruitment(action);
				break;
			case 0x78:
				ReadSetOutput(action);
				break;
			default:
				printf("Action: 0x%02X%02X%02X%02X Size: %d Position: %d\n", action.Id, action.Info1, action.Info2, action.Info3, action.Size, firstPosition);
				_reader->SetPosition(firstPosition + action.Size);
		}

		int secondPosition = _reader->GetPosition();

		if (secondPosition < firstPosition + action.Size)
		{
			_reader->SetPosition(firstPosition + action.Size);
		}
	}

private:
	void ReadUnitInteraction(Action action)
	{
		int objectId = _reader->ReadInteger();
		int unitCount = _reader->ReadInteger();
		float xCoord = _reader->ReadFloat();
		float yCoord = _reader->ReadFloat();
		
		printf("Player %d: Interact with object %d on Coords x: %.2f y: %.2f ", action.Info1, objectId, xCoord, yCoord);

		if (unitCount < 255 && unitCount > 0)
		{
			printf("with units [");
			for (int i = 0; i < unitCount; i++)
			{
				int unitId = _reader->ReadInteger();

				if (i > 0)
				{
					printf(", ");
				}

				printf("%d", unitId);
			}

			printf("]");
		}
		else
		{
			printf("with last selected units");
		}

		int timestamp = _reader->ReadInteger();

		printf("\n");
	}

	void ReadMovement(Action action)
	{
		int randomNumber = _reader->ReadInteger();
		int unitCount = _reader->ReadInteger();
		float xCoord = _reader->ReadFloat();
		float yCoord = _reader->ReadFloat();
		
		printf("Player %d: Moving units on Coords x: %.2f y: %.2f ", action.Info1, xCoord, yCoord);

		if (unitCount < 255 && unitCount > 0)
		{
			printf(" [");
			for (int i = 0; i < unitCount; i++)
			{
				int unitId = _reader->ReadInteger();

				if (i > 0) {
					printf(", ");
				}

				printf("%d", unitId);
			}

			printf("]");
		}
		else
		{
			printf("of last selection");
		}

		int timestamp = _reader->ReadInteger();

		printf("\n");
	}

	void ReadSetOutput(Action action)
	{
		int randomNumber1 = _reader->ReadInteger();
		int randomNumber2 = _reader->ReadInteger();

		float x = _reader->ReadFloat();
		float y = _reader->ReadFloat();

		int objectId = _reader->ReadInteger();

		printf("Player X: Set Output of Object %d to x: %.2f and y: %.2f\n", objectId, x, y);
	}

	void ReadBuilding(Action action)
	{
		byte unitCount = action.Info1;
		byte playerId = action.Info2;

		float x = _reader->ReadFloat();
		float y = _reader->ReadFloat();

		int buildingId = _reader->ReadInteger();

		int randomNumber1 = _reader->ReadInteger();
		int randomNumber2 = _reader->ReadInteger();

		printf("Player %d: Building %d on Coords: x:%.2f y:%.2f [", playerId, buildingId, x, y);
		
		for (int i = 0; i < unitCount; i++)
		{
			int unitId = _reader->ReadInteger();
			
			if (i > 0)
			{
				printf(", ");
			}

			printf("%d", unitId);
		}

		printf("]\n");
	}

	void ReadRecruitment(Action action)
	{
		int buildingId = _reader->ReadInteger();

		short unitId = _reader->ReadShort();
		short unitCount = _reader->ReadShort();

		printf("Player X: Recruiting %d x%d in Building %d\n", unitId, unitCount, buildingId);
	}

	void ReadResearch(Action action)
	{
		int buildingId = _reader->ReadInteger();

		short playerId = _reader->ReadShort();
		short researchId = _reader->ReadShort();

		printf("Player %d: Research %d in Building %d\n", playerId, researchId, buildingId);
	}

	void ReadAndPrintIntegers(int count)
	{
		for (int i = 0; i < count; i++)
		{
			int number = _reader->ReadInteger();

			printf(" %d", number);
		}

		printf("\n");
	}
};