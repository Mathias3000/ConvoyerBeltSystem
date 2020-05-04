#include <cstdio>
#include "TestFunctions.h"
#include "systemManager.h"

StateMachine* myStateMachine;
Keyboard* myKeyboard;
pthread_t threadKeyboard;

int main()
{
    printf("hello from ConvoyerBeltSystem!\n");
	
	SystemManager* systemManagerTest;
	systemManagerTest = new SystemManager;
	systemManagerTest->init();
	pthread_create(&threadKeyboard, NULL, testSM, NULL);
	systemManagerTest->startStateMachine();
	
    //testTCPServer();
	//testMotor(0);
	//testADC();
    //testKeyBoard();
	//testKeyBoard();
	//testTCPServer();
	
	

    return 0;
}
