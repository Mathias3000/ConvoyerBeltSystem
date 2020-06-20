#include <cstdio>
#include "TestFunctions.h"
#include "MotorController.h"
#include "ConveyorBelt.h"

// needed for some tests to work (e.g. testQEP)
MotorController* myMotorController;

using namespace std;

// predefine static variables for local and chain mode
LocalMode* LocalMode::instance = NULL;
ChainMode* ChainMode::instance = NULL;

int main()
{
	
	testStateManager();

  

    return 0;
}
