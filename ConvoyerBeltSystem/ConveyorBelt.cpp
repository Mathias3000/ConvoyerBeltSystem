#include "ConveyorBelt.h"

ConveyorBelt::ConveyorBelt()
{
	currentMode = new LocalMode();
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
	if (((LocalMode*)currentMode)->userInterface->updateCommunicationType && ((LocalMode*)currentMode)->userInterface != NULL) 
	{
		currentMode->communication = ((LocalMode*)currentMode)->userInterface;
		((LocalMode*)currentMode)->userInterface->updateCommunicationType = false;
	}
	else if (((LocalMode*)currentMode)->telnetServer->updateCommunicationType && ((LocalMode*)currentMode)->telnetServer != NULL)
	{
		currentMode->communication = ((LocalMode*)currentMode)->telnetServer;
		((LocalMode*)currentMode)->telnetServer->updateCommunicationType = false;
	}
	else if (((ChainMode*)currentMode)->network->leftConveyorBelt->updateCommunicationType && ((ChainMode*)currentMode)->network->leftConveyorBelt != NULL)
	{
		currentMode->communication = ((ChainMode*)currentMode)->network;
		((ChainMode*)currentMode)->network->leftConveyorBelt->updateCommunicationType = false;

	}
	else if (((ChainMode*)currentMode)->network->rightConveyorBelt->updateCommunicationType && ((ChainMode*)currentMode)->network->rightConveyorBelt != NULL)
	{
		currentMode->communication = ((ChainMode*)currentMode)->network;
		((ChainMode*)currentMode)->network->rightConveyorBelt->updateCommunicationType = false;

	}
	else if (((ChainMode*)currentMode)->network->master->updateCommunicationType && ((ChainMode*)currentMode)->network->master != NULL)
	{
		currentMode->communication = ((ChainMode*)currentMode)->network;
		((ChainMode*)currentMode)->network->master->updateCommunicationType = false;

	}
	else
	{

	}
	updateMutex.unlock();
}
