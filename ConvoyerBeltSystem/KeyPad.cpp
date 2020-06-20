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
		// TODO: improve
		// use timer. Check in each case, whether a reapeated sendEvent is allowed
		// https://en.cppreference.com/w/cpp/chrono/c/clock

		// reads keyboard input and sends corresponding event
		readValue = keyboard->getPressedKey();

		switch (readValue)
		{
		case '1':
			// motorController->direction = 1;		// way to avoid this: add seperate event-string & action 
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdDirectionKeyPad");
			break;

		case '2':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdDirectionKeyPad");
			break;

		case'3':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdFollowProfile");		// Start motor/start movement
			break;

		case '4':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdStopMotor");
			break;

		case 'F':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdChain");
			break;

		case 'E':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdLocal");
			break;

		case 'D':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdSetSpeedPoti");
			break;

		default:
			break;
		}
		usleep(150000);
	}
}

string KeyPad::readKey()
{
	return string(1, keyboard->getPressedKey());
}

char KeyPad::getLastKeyInput()
{
	return lastValue;
}
