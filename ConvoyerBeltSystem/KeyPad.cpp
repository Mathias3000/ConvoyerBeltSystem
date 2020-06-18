#include "KeyPad.h"
// TODO: Check if this kind of globaal variable usage actually works correctly. 
// MotorController* motorController;

KeyPad::KeyPad()
{
	keyboard = new Keyboard();
	thread* keyPadThread = new thread(&KeyPad::handleKeyInput, this);
	
}

KeyPad::~KeyPad()
{
	delete this;
}

void KeyPad::handleKeyInput()
{
	while (true)
	{
		// reads keyboard input and sends corresponding event
		readValue = keyboard->getPressedKey();

		switch (readValue)
		{
		case '1':
			// motorController->direction = 1;		// way to avoid this: add seperate event-string & action 
			myStateMaschine->sendEvent("RecvCmdDirectionRight");
			break;

		case '2':
			myStateMaschine->sendEvent("RecvCmdDirectionLeft");
			break;

		case'3':
			myStateMaschine->sendEvent("RecvCmdFollowProfile");		// Start motor/start movement
			break;

		case '4':
			myStateMaschine->sendEvent("RecvCmdStopMotor");
			break;

		case 'F':
			myStateMaschine->sendEvent("RecvCmdChain");
			break;

		case 'E':
			myStateMaschine->sendEvent("RecvCmdLocal");
			break;

		case 'D':
			myStateMaschine->sendEvent("RecvCmdSetSpeedPoti");
			break;

		default:
			break;
		}

		usleep(50000);	// 50ms sleep

	}
}

string KeyPad::readKey()
{
	return string(1, keyboard->getPressedKey());
}

char KeyPad::getLastKeyInput()
{
	return readValue;
}
