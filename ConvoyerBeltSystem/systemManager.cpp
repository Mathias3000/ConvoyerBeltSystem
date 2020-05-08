#include "SystemManager.h"

SystemManager::SystemManager()
{
	n = m = 0;
	keyBoard = new Keyboard();
	stateMaschine = new StateMachine();
	init();
}

SystemManager::~SystemManager()
{
	delete this;
}

void SystemManager::init()
{

	// Define state charts
	// Local Mode Chart
	stateMaschine->tab[0][0] = new TableEntry("Idle", "Local", "RecvCmdLocal", 0, noAction, noCondition);
	stateMaschine->tab[0][1] = new TableEntry("Local", "Local", "RecvCmdSpeed", 0, actionSetSpeed, noCondition);
	stateMaschine->tab[0][2] = new TableEntry("Local", "Local", "RecvCmdDirection", 0, actionSetDirection, noCondition);
	stateMaschine->tab[0][3] = new TableEntry("Local", "FollowProfile", "RecvCmdFollowProfile", 0, actionFollowProfile, noCondition);
	stateMaschine->tab[0][4] = new TableEntry("FollowProfile", "Local", "motorControllerFinishedProfile", 0, noAction, noCondition);
	stateMaschine->tab[0][5] = new TableEntry("Local", "Chain", "RecvCmdChain", 0, noAction, noCondition);

	// FollowProfile
	stateMaschine->tab[1][0] = new TableEntry("FollowProfile", "Local", "Timer0", 20, actionSetSpeedAndSteps, conditionTotalSteps);
	
	// Chain
	stateMaschine->tab[2][0] = new TableEntry("Idle", "Chain", "RecvCmdChain", 0, noAction, noCondition);
	stateMaschine->tab[2][1] = new TableEntry("Chain", "Chain", "RecvCmdSpeed", 0, actionSetSpeed, noCondition);
	stateMaschine->tab[2][2] = new TableEntry("Chain", "Requested", "RecvCmdRequest", 0, noAction, noCondition);
	stateMaschine->tab[2][3] = new TableEntry("Requested", "Requested", "RecvCmdRequest", 0, actionHandleRequest_Wait, noCondition);
	stateMaschine->tab[2][4] = new TableEntry("Requested", "ReceivingPayload", "motorControllerReadToRecvPayload", 0, actionHandleRequest_Ready, noCondition);
	stateMaschine->tab[2][5] = new TableEntry("ReceivingPayload", "ReceivingPayload", "RecvCmdRequest", 0, actionHandleRequest_Wait, noCondition);
	stateMaschine->tab[2][6] = new TableEntry("ReceivingPayload", "FollowProfile", "SendRelease", 0, actionFollowProfile, noCondition);
	stateMaschine->tab[2][7] = new TableEntry("FollowProfile", "FollowProfile", "RecvCmdRequest", 0, actionHandleRequest_Wait, noCondition);
	stateMaschine->tab[2][8] = new TableEntry("FollowProfile", "Requesting", "motorControllerFinishedProfile", 0, actionSendRequest, noCondition);
	stateMaschine->tab[2][9] = new TableEntry("Requesting", "Requesting", "RecvCmdRequest", 0, actionHandleRequest_Wait, noCondition);
	stateMaschine->tab[2][10] = new TableEntry("Requesting", "Requesting", "RecvCmdWait", 0, actionMotorStop, noCondition);
	stateMaschine->tab[2][11] = new TableEntry("Requesting", "PassLoad", "RecvCmdReady", 0, actionMotorMove, noCondition);
	stateMaschine->tab[2][12] = new TableEntry("PassLoad", "Chain", "RecvCmdRelease", 0, actionMotorStop, noCondition);

	// Initialize timer names for all diagrams
	stateMaschine->timerNames[0] = "Timer0";

	// Initialize line numbers for all diagrams
	stateMaschine->lines[0] = 6;	// Anzahl der Teilen bei den Tabellen oben
	stateMaschine->lines[1] = 1;
	stateMaschine->lines[2] = 13;

	// Initialize first state for all diagrams
	stateMaschine->actualState[0] = "Idle";
	stateMaschine->actualState[1] = "FollowProfile";
	stateMaschine->actualState[2] = "Idle";

	// Set the actual number of diagrams
	stateMaschine->diagrams = 3;

	// Initialize state machine
	stateMaschine->init();

	// Start timer for each diagram which needs one in the first state!
	// In my case these are diagram 0 and 2
	stateMaschine->diaTimerTable[0]->startTimer(stateMaschine->tab[1][0]->eventTime);

	// Initial actions can be done here, if needed!
	n = 0;
	m = 0;

}

void SystemManager::startStateMaschine()
{
	stateMaschine->runToCompletion();
}



// Defining global functions
// ACTIONS
void noAction() {
	cout << "No action" << endl;
	return;
}

void actionSetSpeed() {
	
	cout << "Set speed. " << endl;
}

void actionSetDirection(){

	cout << "Set direction. " << endl;
}

void actionFollowProfile() {

	cout << "Start following profile. " << endl;
}

void actionSetSpeedAndSteps() {

	cout << "Set speed and increment steps" << endl;;
}

void actionHandleRequest_Wait() {

	cout << "Handling reqeuest ... sending wait ... " << endl;
}

void actionHandleRequest_Ready() {

	cout << "Handling reqeuest ... sending ready ... " << endl;
}

void actionSendRequest() {

	cout << "Sending request ... " << endl;
}

void actionMotorStop() {

	cout << "Motor stopped. " << endl;
}

void actionMotorMove() {

	cout << "Motor moving slowly ... " << endl;
}


// CONDITIONS
bool noCondition() {
	return true;
}

bool conditionTotalSteps(){

	cout << "Total steps > 400 " << endl;
	return true;	// Change for later implementation
}
