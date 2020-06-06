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
	//myMotorController->stop();
	SystemManager* systemManagerTest;
	systemManagerTest = new SystemManager;
	systemManagerTest->init();

	//myMotorController->setSpeedInRPM(100);

	thread threadKeyboard(testSM);
	//thread threadTestController(testController);
	thread threadQEP(testQEP);

	systemManagerTest->startStateMachine();
	//testTCPServer();
	//testMotor(0);
	//testADC();
    //testKeyBoard();

    return 0;
}
