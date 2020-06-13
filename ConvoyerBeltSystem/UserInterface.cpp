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
	return nullptr;
}
