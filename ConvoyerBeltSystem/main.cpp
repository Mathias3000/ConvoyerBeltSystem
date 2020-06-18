#include <cstdio>
#include "TestFunctions.h"
#include "systemManager.h"
#include "MotorController.h"
#include <pthread.h>
#include "ConveyorBelt.h"

Controller* myController;
Encoder* myEncoder;
Motor* myMotor;
SpeedProfile* mySpeedProfile;
MotorController* myMotorController;
ConveyorBelt* myConveyorBelt;
StateMachine* myStateMaschine;

using namespace std;

// predefine static variables for local and chain mode
LocalMode* LocalMode::instance = NULL;
ChainMode* ChainMode::instance = NULL;

int main()
{
	myStateMaschine = new StateMachine();
	myStateMaschine->init();

	testPotentiometer();

	testStateManager();

  printf("hello from ConvoyerBeltSystem!\n");


    return 0;
}
