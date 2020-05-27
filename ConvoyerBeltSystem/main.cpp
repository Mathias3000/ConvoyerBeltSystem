#include <cstdio>
#include "TestFunctions.h"
#include "systemManager.h"

using namespace std;

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
	myMotorController->setSpeedPercent(50);
	myMotor->stopMotor();
	SystemManager* systemManagerTest;
	systemManagerTest = new SystemManager;
	systemManagerTest->init();
	thread threadKeyboard(testSM);
	thread threadTestController(testController);
	systemManagerTest->startStateMachine();
	

	//thread threadQEP(testQEP);
    //testTCPServer();
	//testMotor(0);
	//testADC();
    //testKeyBoard();
    return 0;
}
