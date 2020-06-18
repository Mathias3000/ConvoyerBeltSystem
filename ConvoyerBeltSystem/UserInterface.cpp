#include "UserInterface.h"

UserInterface::UserInterface()
{
	keyPad = new KeyPad();
	potentiometer = new Potentiometer();
}

UserInterface* UserInterface::getInstance()
{
	if (instance == NULL) {
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
	Command* receivedCommand;
	// KeyPad
	receivedCommand->data = keyPad->readKey();
	receivedCommand->src = KeyPadLocal;
	receivedCommand->dest = Self;
	// Check if poti value if wanted: key = 'D'
	// Maybe SM is not fast enough to read "D" again after sending Event upon reading it the first time (when using readKey())
	// Fix: save read value in buffer
	if (keyPad->getLastKeyInput() == 'D') {
		// Potentiometer
		receivedCommand->data = to_string(potentiometer->getSpeed());
		receivedCommand->src = PotentiometerLocal;
	}

	return receivedCommand;
}

Command* UserInterface::pollingData()
{
	while (true)
	{
		string readValue = keyPad->readKey();

	}

	return nullptr;
}
