
#ifndef SYSTEMMANAGER_H_
#define SYSTEMMANAGER_H_

#include "stateMachine.h"
#include "keyboard.h"
#include "myFunctions.h"
#include "stateTable.h"
#include <stdio.h>
#include "Motor.h"

extern int stepCounterFollowProf;

class SystemManager {
public:
	SystemManager();
	~SystemManager();
	void init();
	void startStateMachine();
private:
	
};

#endif // SYSTEMMANAGER_H_
