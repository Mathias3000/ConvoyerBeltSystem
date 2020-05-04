#include <cstdio>
#include "TestFunctions.h"
#include "Motor.h"
#include "MotorController.h"

Motor* myMotor;

int main()
{
	int error = 0;
    printf("hello from ConvoyerBeltSystem!\n");
	myMotor = new Motor;
	error = myMotor->initMotor(); // test the initialization
	myMotor->startMotor(0);
	sleep(3);
	myMotor->stopMotor();

    //testTCPServer();
	//testMotor(0);
	//testADC();

    //testKeyBoard();


    return 0;
}
