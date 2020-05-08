
#ifndef SYSTEMMANAGER_H_
#define SYSTEMMANAGER_H_

#include <stdio.h>

#include "stateMachine.h"
#include "keyboard.h"
#include "myFunctions.h"
#include "stateTable.h"
#include "MotorController.h"

extern MotorController* myMotorController;

class SystemManager {
public:
	SystemManager();
	~SystemManager();
	void init();
	void startStateMachine();
private:
};

#endif // SYSTEMMANAGER_H_
