#include "ConveyorBelt.h"

ConveyorBelt::ConveyorBelt()
{
	init();
}

ConveyorBelt::~ConveyorBelt()
{
	delete this;
}

void ConveyorBelt::updateCurrentCommunicationType()
{
	updateMutex.lock();
	// Check in LocalMode and ChainMode
	// Check if update flag is set and the instance is not NULL
	if (((LocalMode*)currentMode)->userInterface != NULL) {
		if (((LocalMode*)currentMode)->userInterface->updateCommunicationType)
		{
			currentMode->communication = ((LocalMode*)currentMode)->userInterface;
			((LocalMode*)currentMode)->userInterface->updateCommunicationType = false;
		}
	}
	else if (((LocalMode*)currentMode)->telnetServer != NULL)
	{
		if (((LocalMode*)currentMode)->telnetServer->updateCommunicationType)
		{
			currentMode->communication = ((LocalMode*)currentMode)->telnetServer;
			((LocalMode*)currentMode)->telnetServer->updateCommunicationType = false;
		}
	}
	else if (((ChainMode*)currentMode)->network->leftConveyorBelt != NULL)
	{
		if (((ChainMode*)currentMode)->network->leftConveyorBelt->updateCommunicationType)
		{
			currentMode->communication = ((ChainMode*)currentMode)->network;
			((ChainMode*)currentMode)->network->leftConveyorBelt->updateCommunicationType = false;
		}
	}
	else if (((ChainMode*)currentMode)->network->rightConveyorBelt != NULL)
	{
		if (((ChainMode*)currentMode)->network->rightConveyorBelt->updateCommunicationType)
		{

		}
	}
	else if (((ChainMode*)currentMode)->network->master != NULL)
	{
		if (((ChainMode*)currentMode)->network->master->updateCommunicationType)
		{
			currentMode->communication = ((ChainMode*)currentMode)->network;
			((ChainMode*)currentMode)->network->master->updateCommunicationType = false;
		}
	}
	else
	{

	}
	updateMutex.unlock();
}

void ConveyorBelt::resetCommunicationFlags()
{
}

void ConveyorBelt::init()
{
	// Instiate local and chain mode + set local default
	// use singleton design pattern to avoid multiple instances of local and chain mode
	currentMode = ChainMode::getInstance();
	currentMode = LocalMode::getInstance();
}
