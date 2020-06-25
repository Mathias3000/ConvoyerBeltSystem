#include "UserInterface.h"

UserInterface::UserInterface()
{
	keyPad = new KeyPad();
	potentiometer = new Potentiometer();
}

UserInterface* UserInterface::getInstance()
{
	if (instance == nullptr) {
		instance = new UserInterface();
	}
	return instance;
}

UserInterface::~UserInterface()
{
	delete this;
}

Command* UserInterface::parse()
{
	Command* receivedCommand = new Command();
	// KeyPad
	receivedCommand->data = keyPad->getLastKeyInput();
	receivedCommand->src = KeyPadLocal;
	receivedCommand->dest = Self;
	// Check if poti value if wanted: key = 'D'
	// Maybe SM is not fast enough to read "D" again after sending Event upon reading it the first time (when using readKey())
	// Fix: save read value in buffer
	if (keyPad->getLastKeyInput() == 'D') {	
		receivedCommand->data = to_string(potentiometer->getSpeed());
		receivedCommand->data = to_string(potentiometer->getSpeed());
		receivedCommand->src = PotentiometerLocal;
	}
	else if (keyPad->getLastKeyInput() == '1') {	// dir = right
		receivedCommand->data = 'r';
	} 
	else if (keyPad->getLastKeyInput() == '2') {
		receivedCommand->data = 'l';
	}
	return receivedCommand;
}

