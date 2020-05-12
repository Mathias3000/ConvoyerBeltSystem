#include <cstdio>
#include "TestFunctions.h"
#include "systemManager.h"


int main()
{
    printf("hello from ConvoyerBeltSystem!\n");
	Encoder* myEncoder;
	Motor* myMotor;
	SpeedProfile* mySpeedProfile;
	Controller* myController;
	myController = new Controller;
	myEncoder = new Encoder;
	myMotor = new Motor(myEncoder, myController);
	mySpeedProfile = new SpeedProfile;
	myMotorController = new MotorController(myMotor, mySpeedProfile);
	myMotorController->setSpeed(50);
	myMotor->stopMotor();
	SystemManager* systemManagerTest;
	systemManagerTest = new SystemManager;
	systemManagerTest->init();
	pthread_t threadQEP;
	pthread_create(&threadQEP, NULL, testQEP, NULL);
	pthread_t threadKeyboard;
	pthread_create(&threadKeyboard, NULL, testSM, NULL);
	systemManagerTest->startStateMachine();
    //testTCPServer();
	//testMotor(0);
	//testADC();
    //testKeyBoard();
    return 0;
}
