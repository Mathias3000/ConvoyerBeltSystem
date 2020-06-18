#include <cstdio>
#include "TestFunctions.h"
#include "systemManager.h"

using namespace std;

int main()
{
    printf("hello from ConvoyerBeltSystem!\n");
	Display* myDisplay = new Display;
	/*
	char a[MAX_CONS_LEN] = "this is a string to diplay!\n";
	myDisplay->displayLine(a);
	*/

	
	Encoder* myEncoder;
	Motor* myMotor;
	SpeedProfile* mySpeedProfile;
	Controller* myController;
	myController = new Controller;
	myEncoder = new Encoder;
	myMotor = new Motor(myEncoder, myController);
	mySpeedProfile = new SpeedProfile;
	myMotorController = new MotorController(myMotor, mySpeedProfile);
	SystemManager* systemManagerTest;
	systemManagerTest = new SystemManager;
	systemManagerTest->init();
	thread threadKeyboard(testSM);
	thread threadQEP(testQEP);
	systemManagerTest->startStateMachine();
	
	//testTCPServer();
	//testMotor(0);
	//testADC();
    //testKeyBoard();
	
	
    return 0;
}
