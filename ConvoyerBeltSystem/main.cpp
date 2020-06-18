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

// predefine local and chain mode static
LocalMode* LocalMode::instance = NULL;
ChainMode* ChainMode::instance = NULL;

int main()
{
	myStateMaschine = new StateMachine();
	myStateMaschine->init();

	testPotentiometer();

	testStateManager();

    printf("hello from ConvoyerBeltSystem!\n");

	testTCPClient();
	testTCPServer();
	
	myController = new Controller;
	myEncoder = new Encoder;
	myMotor = new Motor(myEncoder, myController);
	mySpeedProfile = new SpeedProfile;
	myMotorController = new MotorController(myMotor, mySpeedProfile);
	myMotorController->setSpeed(100);
	SystemManager* systemManagerTest;
	systemManagerTest = new SystemManager;
	systemManagerTest->init();
	pthread_t threadKeyboard;
	pthread_create(&threadKeyboard, NULL, testSM, NULL);
	systemManagerTest->startStateMachine();
	
    //testTCPServer();
	//testMotor(0);
	//testADC();
    //testKeyBoard();

    return 0;
}
