#include <cstdio>
#include "TestFunctions.h"
#include "systemManager.h"


int main()
{
    printf("hello from ConvoyerBeltSystem!\n");

    //testTCPServer();
	//testMotor(0);
	//testADC();
    //testKeyBoard();
	//testKeyBoard();
	//testTCPServer();
	
	SystemManager* systemManagerTest = new SystemManager;
	systemManagerTest->init();

	pthread_t threadKeyboard;
	pthread_create(&threadKeyboard, NULL, testSM, NULL);
	
	systemManagerTest->startStateMachine();
	//pthread_join(threadKeyboard, NULL);

    return 0;
}
