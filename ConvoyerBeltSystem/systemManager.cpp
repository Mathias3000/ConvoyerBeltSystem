#include "SystemManager.h"
#include "SystemManager.h"

SystemManager::SystemManager()
{
	n = m = 0;
	keyBoard = new Keyboard();
	stateMaschine = new StateMachine();
	init();
}

SystemManager::~SystemManager()
{
	delete this;
}
