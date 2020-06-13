#include "UserInterface.h"

UserInterface::UserInterface()
{
	keyPad = new KeyPad();
	potentiometer = new Potentiometer();
}

UserInterface::~UserInterface()
{
	delete this;
}

Command* UserInterface::parse()
{
	Command* recvData = new Command();
	// KeyPad
	recvData->data = keyPad->readKey();
	recvData->src = KeyPadLocal;

	// Check if poti value if wanted: key = 'D'
	// Maybe SM is not fast enough to read "D" again after sending Event upon reading it the first time (when using readKey())
	// Fix: save read value in buffer
	if (keyPad->getLastKeyInput() == 'D') {
		// Potentiometer
		recvData->data = to_string(potentiometer->getValue());
		recvData->src = PotentiometerLocal;
	}

	return recvData;
}
