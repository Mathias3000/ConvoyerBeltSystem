#include <cstdio>
#include "TestFunctions.h"
#include "systemManager.h"
#include "Motor.h"
#include "MotorController.h"
#include <pthread.h>

Motor* myMotor = new Motor;
SpeedProfile* mySpeedProfile = new SpeedProfile;
MotorController* myMotorController = new MotorController(myMotor, mySpeedProfile);

int main()
{
    printf("hello from ConvoyerBeltSystem!\n");
	
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
