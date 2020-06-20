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
TelnetServer* TelnetServer::instance = NULL;
UserInterface* UserInterface::instance = NULL;
Network* Network::instance = NULL;

int main()
{

    StateManager* sm = new StateManager();
    sm->init();
    sm->startStateMaschine();

    return 0;
}
