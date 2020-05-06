#include <cstdio>
#include "TestFunctions.h"
#include "Motor.h"
#include "MotorController.h"
#include <pthread.h>


int main()
{
    printf("hello from ConvoyerBeltSystem!\n");
	Motor* myMotor;
	myMotor = new Motor;

	pthread_t threadRamp;
	//pthread_join(threadRamp, NULL);


	myMotor->initMotor();
	myMotor->setSpeed(35);
	myMotor->stopMotor();
	pthread_create(&threadRamp, NULL, followProfile, NULL);
	myMotor->followProfile(Right);
	
    //testTCPServer();
	//testMotor(0);
	//testADC();
    //testKeyBoard();

    testKeyBoard();


    //testTCPServer();
	//testMotor(0);
	testADC();


    return 0;
}
