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

void ConveyorBelt::stopDisplayUI()
{
	this->stop == true;
}

void ConveyorBelt::init()
{
	// Instiate local and chain mode + set local default
	// use singleton design pattern to avoid multiple instances of local and chain mode
	currentMode = ChainMode::getInstance();
	currentMode = LocalMode::getInstance();
	//this->workerDisplayUI = thread(&ConveyorBelt::displayUI, this); //start thread Display UI
}

int ConveyorBelt::displayUI()
{
	/*
	char displayLine[MAX_CONS_LEN];
	const char* tempData;
	string tempString;
	int configuredSpeed, actualSpeed;
	Direction configuredDirection;
	MotorState actualMotorState;

	//mögliche Telnet Befehle, Keypad Befehle ganz oben anzeigen
	char* topLines[MAXTOPLINES] = { "Possible Keypad commands:", 
		"1: right, 2: left, 3: follow Profile, 4: stop,",
		"F: go to chain mode, D: Set speed via potentiometer",
		"Possible Telnet commands:", 
		"tel:start, tel:stop, tel dir:right, tel dir:left, tel speed:xxxx" 
	};

	this->currentMode->display->displayClear();

	while (!stop)
	{
		//display the very top lines
		for (int i = 0; i < MAXTOPLINES; i++) {
			this->currentMode->display->displayLine(topLines[i]);
		}
		//display configured speed:
		configuredSpeed = currentMode->motorController->getConfiguredSpeedRPM();
		tempString = to_string(configuredSpeed);
		tempData = tempString.c_str();
		strcpy(displayLine, "Configured speed is: ");
		strcat(displayLine, tempData);
		this->currentMode->display->displayLine(displayLine);
		//display configured direction:
		configuredDirection = currentMode->motorController->getConfiguredDirection();
		if (configuredDirection == Right) {
			strcpy(displayLine, "Configured direction is: Right");
			this->currentMode->display->displayLine(displayLine);
		}
		else if (configuredDirection == Left) {
			strcpy(displayLine, "Configured direction is: Left");
			this->currentMode->display->displayLine(displayLine);
		};
		//display actual motor state:
		actualMotorState = currentMode->motorController->getMotorState();
		if (actualMotorState == movingLeft) {
			strcpy(displayLine, "Motor state: left");
			this->currentMode->display->displayLine(displayLine);
		}
		else if (actualMotorState == movingRight) {
			strcpy(displayLine, "Motor state: right");
			this->currentMode->display->displayLine(displayLine);
		}
		else if (actualMotorState == Stop) {
			strcpy(displayLine, "Motor state: stopped");
			this->currentMode->display->displayLine(displayLine);
		};
		//display currents speed:
		actualSpeed = currentMode->motorController->getCurrentSpeedRPM();
		tempString = to_string(actualSpeed);
		tempData = tempString.c_str();
		strcpy(displayLine, "Actual speed is: ");
		strcat(displayLine, tempData);
		this->currentMode->display->displayLine(displayLine);

		//if in chain mode:
		if(currentMode == ChainMode::getInstance()) {
			strcpy(displayLine, "System in currently chain mode");
			this->currentMode->display->displayLine(displayLine);
			strcpy(displayLine, "current commands from Conveyorbelt right, left and from the master: ");
			this->currentMode->display->displayLine(displayLine);

			//letzte Befehle von Links, Rechts, Master anzeigen

		}
		
		// local mode: in beide Richtungen fahren, gestartet und gestoppt, vor dem starten speed von 100-2200 einstellbar
		if (currentMode == LocalMode::getInstance()) {
			strcpy(displayLine, "System currently in local mode");
			this->currentMode->display->displayLine(displayLine);
		}

		sleep(1);
		this->currentMode->display->displayClear();
	}
	*/
	return 0;
}


