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
