#include <cstdio>
#include "TestFunctions.h"

#include "systemManager.h"

StateMachine* myStateMachine;
Keyboard* myKeyboard;
pthread_t threadKeyboard;

#include "Motor.h"
#include "MotorController.h"
#include <pthread.h>



int main()
{
    printf("hello from ConvoyerBeltSystem!\n");

	
	SystemManager* systemManagerTest;
	systemManagerTest = new SystemManager;
	systemManagerTest->init();
	pthread_create(&threadKeyboard, NULL, testSM, NULL);
	systemManagerTest->startStateMachine();

	Motor* myMotor;
	myMotor = new Motor;
	myMotor->initMotor();
	myMotor->setSpeed(50);
	myMotor->startMotor(Right);
	sleep(3);
	myMotor->stopMotor();

	
    //testTCPServer();
	//testMotor(0);
	//testADC();
    //testKeyBoard();


	


    return 0;
}
