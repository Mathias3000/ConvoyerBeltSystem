#include <cstdio>
#include "TestFunctions.h"
#include "systemManager.h"
#include "Motor.h"
#include "MotorController.h"
#include <pthread.h>

extern Motor* myMotor; //declared in systemManager

int main()
{
    printf("hello from ConvoyerBeltSystem!\n");
	
	myMotor = new Motor;
	myMotor->initMotor();
	myMotor->setSpeed(50);
	myMotor->stopMotor();
	pthread_t threadKeyboard;
	SystemManager* systemManagerTest;
	systemManagerTest = new SystemManager;
	systemManagerTest->init();
	pthread_create(&threadKeyboard, NULL, testSM, NULL);
	systemManagerTest->startStateMachine();

    //testTCPServer();
	//testMotor(0);
	//testADC();
    //testKeyBoard();
    return 0;
}
