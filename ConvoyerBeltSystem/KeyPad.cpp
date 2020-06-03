#include "KeyPad.h"
// TODO: Check if this kind of globaal variable usage actually works correctly. 
// MotorController* motorController;

KeyPad::KeyPad()
{
	keyboard = new Keyboard();
}

KeyPad::~KeyPad()
{
	delete this;
}

void KeyPad::readKey()
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
		myStateMaschine->sendEvent("RecvCmdReadPoti");
		break;

	default:
		break;
	}

}