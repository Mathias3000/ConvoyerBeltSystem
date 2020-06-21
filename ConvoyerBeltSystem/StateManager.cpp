#include "StateManager.h"

// I need these global variables so that I can access them in my global action functions
// Tip: use prefix "my" for testing with global variables

mutex mtxKeys;
int n, m;		
StateMachine* myStateMaschine;
ConveyorBelt* myConveyorBelt;

StateManager::StateManager()
{
	myConveyorBelt = new ConveyorBelt();
}

StateManager::~StateManager()
{
	delete this;
}

void StateManager::init()
{
	// TODO: use defines for state names

	myStateMaschine = new StateMachine();

	// DEFINE STATE CHARTS
	// Local Mode Chart

	// myStateMaschine->tab[0][0] = new TableEntry("Idle", "Local", "RecvCmdLocal", 0, startLocalMode, noCondition);
	myStateMaschine->tab[0][0] = new TableEntry("Local", "Chain", "RecvCmdChain", 0, selectChainMode, noCondition);	// reset to local mit cmd
	myStateMaschine->tab[0][1] = new TableEntry("Chain", "Local", "Reset", 0, noAction, noCondition);	// reset to local 
	myStateMaschine->tab[0][2] = new TableEntry("Local", "Local", "RecvCmdSetSpeedPoti", 0, setSpeedPotentiometer, noCondition);
	myStateMaschine->tab[0][3] = new TableEntry("Local", "Local", "RecvCmdSetSpeedTelnet", 0, setSpeedTelnet, noCondition);
	myStateMaschine->tab[0][4] = new TableEntry("Local", "Local", "RecvCmdDirectionKeyPad", 0, setDirectionKeyPad, noCondition);
	myStateMaschine->tab[0][5] = new TableEntry("Local", "Local", "RecvCmdDirectionTelnet", 0, setDirectionTelnet, noCondition);
	myStateMaschine->tab[0][6] = new TableEntry("Local", "FollowProfile", "RecvCmdFollowProfile", 0, followProfile, noCondition);
	myStateMaschine->tab[0][7] = new TableEntry("FollowProfile", "FollowProfile", "Timer0", 20, updateMotorController, isProfileFinished);
	myStateMaschine->tab[0][8] = new TableEntry("FollowProfile", "Local", "finishedProfile", 0, finishedProfile, noCondition);

	// Chain Chart
	// myStateMaschine->tab[1][0] = new TableEntry("Idle", "Chain", "RecvCmdChain", 0, startChainMode, noCondition);
	myStateMaschine->tab[1][0] = new TableEntry("Chain", "Local", "RecvCmdLocal", 0, selectLocalMode, noCondition);
	myStateMaschine->tab[1][1] = new TableEntry("Local", "Chain", "Reset", 0, noAction, noCondition);
	myStateMaschine->tab[1][2] = new TableEntry("Chain", "Chain", "RecvCmdSetSpeedPoti", 0, setSpeedPotentiometer, noCondition);
	myStateMaschine->tab[1][3] = new TableEntry("Chain", "Chain", "RecvCmdSetSpeedTelnet", 0, setSpeedTelnet, noCondition);
	myStateMaschine->tab[1][4] = new TableEntry("Chain", "Requested", "RecvCmdRequest", 0, handleRequest, noCondition);
	myStateMaschine->tab[1][5] = new TableEntry("Requested", "Requested", "RecvCmdRequest", 0, handleRequestRepeat, noCondition);
	myStateMaschine->tab[1][6] = new TableEntry("Requested", "ReceivingPayload", "ReadyToRecvPayload", 0, startSlowMovement, readyToReceive);
	myStateMaschine->tab[1][7] = new TableEntry("ReceivingPayload", "ReceivingPayload", "RecvCmdRequest", 0, handleRequestRepeat, noCondition);
	myStateMaschine->tab[1][8] = new TableEntry("ReceivingPayload", "ReceivingPayloadFinished", "Timer1", 1000, releasePayload, noCondition);
	myStateMaschine->tab[1][9] = new TableEntry("ReceivingPayloadFinished", "ReceivingPayloadFinished", "RecvCmdRequest", 0, handleRequestRepeat, noCondition);
	myStateMaschine->tab[1][10] = new TableEntry("ReceivingPayloadFinished", "FollowProfile", "ReleasedPayload", 0, followProfile, noCondition);
	myStateMaschine->tab[1][11] = new TableEntry("FollowProfile", "FollowProfile", "Timer1", 20, updateMotorController, isProfileFinished);
	myStateMaschine->tab[1][12] = new TableEntry("FollowProfile", "Requesting", "finishedProfile", 0, requesting, isProfileFinished);
	myStateMaschine->tab[1][13] = new TableEntry("Requesting", "Requesting", "RecvCmdRequest", 0, handleRequestRepeat, noCondition);
	myStateMaschine->tab[1][14] = new TableEntry("Requesting", "Requesting", "RecvCmdWait", 0, handleWait, noCondition);
	myStateMaschine->tab[1][15] = new TableEntry("Requesting", "Passload", "RecvCmdReady", 0, handleReady, noCondition);
	myStateMaschine->tab[1][16] = new TableEntry("Passload", "PassloadCompleted", "Timer1", 1000, completingPassload, noCondition);
	myStateMaschine->tab[1][17] = new TableEntry("Passload", "Passload", "RecvCmdRequest", 0, handleRequestRepeat, noCondition);
	myStateMaschine->tab[1][18] = new TableEntry("PassloadCompleted", "PassloadCompleted", "RecvCmdRequest", 0, handleRequestRepeat, noCondition);
	myStateMaschine->tab[1][19] = new TableEntry("PassloadCompleted", "Chain", "RecvCmdRelease", 0, checkRequestBuffer, noCondition);

	// Initialize timer names for all diagrams
	// e.g. Diagram 0 uses Timer0, ... 
	myStateMaschine->timerNames[0] = "Timer0";
	myStateMaschine->timerNames[1] = "Timer1";

	// Initialize line numbers for all diagrams
	myStateMaschine->lines[0] = 9;	
	myStateMaschine->lines[1] = 20;

	// Initialize first state for all diagrams
	myStateMaschine->actualState[0] = "Local";
	myStateMaschine->actualState[1] = "Chain";

	// Set the actual number of diagrams
	myStateMaschine->diagrams = 2;

	// Initialize state machine
	myStateMaschine->init();

	// Initial actions can be done here, if needed!
	n = 0;
	m = 0;
}

void StateManager::startStateMaschine()
{
	// mtx.lock();
	myStateMaschine->runToCompletion();
	this_thread::sleep_for(chrono::microseconds(50));
	// mtx.unlock();
}

// Defining global functions
// ACTIONS
void startLocalMode()
{
	myConveyorBelt->currentAction = new string("Changing from IDLE to LocalMode. ");
	myConveyorBelt->currentMode = LocalMode::getInstance();
}

void selectLocalMode() {
	cout << "\nChain -> Local" << endl;
	myConveyorBelt->currentMode = LocalMode::getInstance();
	myConveyorBelt->currentAction = new string("Selected Local Mode. ");
	myStateMaschine->sendEvent("Reset");
}

void startChainMode() {
	cout << "\nChanges from IDLE to ChainMode. " << endl;
	myConveyorBelt->currentAction = new string("Changing from IDLE to ChainMode. ");
	myConveyorBelt->currentMode = ChainMode::getInstance();
}

void selectChainMode() {
	cout << "\Local -> Chain" << endl;
	myConveyorBelt->currentMode = ChainMode::getInstance();
	myConveyorBelt->currentAction = new string("Selected Chain Mode. ");
	myConveyorBelt->showDisplayOutput();
	myStateMaschine->sendEvent("Reset");
}


// TODO: use proper function to set speed in motor
void setSpeedPotentiometer()
{
	// cout << "\nLocal -> Local" << endl;

	myConveyorBelt->currentMode->communication = UserInterface::getInstance();
	Command* cmd = myConveyorBelt->currentMode->communication->parse();
	usleep(50000);		
	int speed = stoi(cmd->data);
	myConveyorBelt->currentMode->motorController->setSpeedInRPM(speed);
	myConveyorBelt->currentAction = new string("Set speed with potentiometer. ");
	cout << "\nSet speed with potentiometer to " << speed << " rpm" << endl;
	
}

void setSpeedTelnet()
{
	// cout << "\nLocal -> Local" << endl;

	// read value from telnet cmd
	myConveyorBelt->currentMode->communication = TelnetServer::getInstance();
	Command* cmd = myConveyorBelt->currentMode->communication->parse();
	int speed = stoi(cmd->data);
	myConveyorBelt->currentMode->motorController->setSpeedInRPM(speed);
	myConveyorBelt->currentAction = new string("Set speed to " + to_string(speed) + "with telnet. ");
	cout << "\nSet speed with telnet to " << speed << " rpm" << endl;

}

void setDirectionKeyPad() {
	// cout << "\nLocal -> Local" << endl;

	// read value from telnet cmd
	myConveyorBelt->currentMode->communication = UserInterface::getInstance();
	Command* cmd = myConveyorBelt->currentMode->recv();
	char dir = cmd->data[0];

	if (dir == 'l') {	// left
		myConveyorBelt->currentMode->motorController->setDirection(Direction::Left);
		myConveyorBelt->currentAction = new string("Set direction to left with keyboard. ");
		cout << "Set direction to left" << endl;
	}
	else if (dir == 'r') {
		myConveyorBelt->currentMode->motorController->setDirection(Direction::Right);
		myConveyorBelt->currentAction = new string("Set direction to right with keyboard. ");
		cout << "Set direction to right" << endl;
	}
	else
	{
		cout << "Failed to set direction. Cmd: " << dir << endl;
		myConveyorBelt->currentAction = new string("Failed to set direction with keyboard. ");
	}

}

void setDirectionTelnet() {
	cout << "\nLocal -> Local" << endl;

	// read value from telnet cmd
	myConveyorBelt->currentMode->communication = TelnetServer::getInstance();
	Command* cmd = myConveyorBelt->currentMode->communication->parse();
	char dir = myConveyorBelt->currentMode->communication->parse()->data[0];

	if (dir == 'l') {	// left
		myConveyorBelt->currentMode->motorController->setDirection(Direction::Left);
		myConveyorBelt->currentAction = new string("Set direction to left with telnet. ");
		cout << "Set direction to left" << endl;
	}
	else if (dir == 'r') {
		myConveyorBelt->currentMode->motorController->setDirection(Direction::Right);
		myConveyorBelt->currentAction = new string("Set direction to right with telnet. ");
		cout << "Set direction to right" << endl;
	}
}

void followProfile() {
	if (myConveyorBelt->currentMode->motorController->getConfiguredDirection() == Right) {
		myConveyorBelt->currentMode->motorController->setMotorState(movingRight);

	}
	else if (myConveyorBelt->currentMode->motorController->getConfiguredDirection() == Left) {
		myConveyorBelt->currentMode->motorController->setMotorState(movingLeft);
	}
	Discrete_initialize();
	cout << "\nStarted Profile" << endl;
	myConveyorBelt->currentAction = new string("Started following profile ... ");
}

void finishedProfile() {
	cout << "\nFollowProfile  -> Steps completed -> Local" << endl;
	myConveyorBelt->currentAction = new string("Finished profile. ");
}

void updateMotorController() 
{
	myConveyorBelt->currentMode->motorController->incrementStepCounter();
	myConveyorBelt->currentMode->motorController->followProfile();
	myConveyorBelt->currentAction = new string("Updating profile steps. ");
}

void handleRequest() 
{
	cout << "\nChain -> Requested" << endl;
	myConveyorBelt->currentMode->communication = Network::getInstance();

	Command* cmd = new Command("\nREADY\n", Self, LeftConveyorBelt);
	myConveyorBelt->currentMode->send(cmd);
	myConveyorBelt->currentAction = new string("Handling request from left conveyorbelt. ");
	myStateMaschine->sendEvent("ReadyToRecvPayload");
}

void releasePayload() {
	cout << "\nReceivingPayload -> ReceivingPayloadFinished" << endl;

	// send Event, check happens in condition
	myConveyorBelt->currentMode->communication = Network::getInstance();
	Command* cmd = new Command("\nRELEASE\n", Self, LeftConveyorBelt);
	myConveyorBelt->currentMode->send(cmd);
	myConveyorBelt->currentAction = new string("Received payload and released left conveyorbelt. ");
	myStateMaschine->sendEvent("ReleasedPayload");
}

void handleRequestRepeat() 
{
	cout << "\nRequested -> Requested" << endl;

	// send back wait
	myConveyorBelt->currentMode->communication = Network::getInstance();
	Command* cmd = new Command("\nWAIT\n", Self, LeftConveyorBelt);
	myConveyorBelt->currentMode->send(cmd);
	myConveyorBelt->currentAction = new string("Storing additional requests in queue. ");
	
}

void checkRequestBuffer()
{
	cout << "\nPassload -> Chain" << endl;
	myConveyorBelt->currentAction = new string("Checking Request buffer. ");

	myConveyorBelt->currentMode->communication = Network::getInstance();
	Command* cmd = myConveyorBelt->currentMode->communication->parse();

	int reqBufferCount = stoi(cmd->data) - 1;	// first request is always processed
	if (reqBufferCount > 0) {
		myStateMaschine->sendEvent("RecvCmdRequest");
	}
}

void startSlowMovement()
{
	cout << "\nRequested -> ReceivingPayload" << endl;
	myConveyorBelt->currentAction = new string("Starting slow movement for 1s. ");
	myConveyorBelt->currentMode->motorController->move(myConveyorBelt->currentMode->motorController->getConfiguredDirection());	// correct function?
}

void requesting()
{
	cout << "\nFollowProfile -> Requesting" << endl;
	myConveyorBelt->currentAction = new string("Sent request to right conveyorbelt. ");

	// send request to right
	myConveyorBelt->currentMode->communication = Network::getInstance();
	Command* cmd = new Command("\nREQUEST\n", Self, RightConveyorBelt);
	myConveyorBelt->currentMode->send(cmd);

}

void handleWait()
{
	cout << "\nRequesting -> Requesting" << endl;
	myConveyorBelt->currentAction = new string("Waiting for right conveyorbelt. ");
	// stay in state
	// stop motor
	myConveyorBelt->currentMode->motorController->stop();
}

void handleReady()
{
	cout << "\nRequesting -> Passload" << endl;
	myConveyorBelt->currentAction = new string("Ready to pass load to right conveyorbelt. ");

	myConveyorBelt->currentMode->motorController->move(myConveyorBelt->currentMode->motorController->getConfiguredDirection());
}

void completingPassload()
{
	cout << "\nPassload -> PassloadCompleted" << endl;
	myConveyorBelt->currentAction = new string("Finished passing payload to right conveyorbelt. ");
	myConveyorBelt->currentMode->motorController->stop();
	// reset status to stop
	myConveyorBelt->currentMode->motorController->myMotor->setStatus(MotorState::Stop);

}

// CONDITIONS
bool noCondition() {
	return true;
}

bool falseCondition()
{
	return false;
}

bool isProfileFinished() {
	int steps = myConveyorBelt->currentMode->motorController->getStepCounter();
	MotorState state = myConveyorBelt->currentMode->motorController->getMotorState();
	Direction direction = myConveyorBelt->currentMode->motorController->getConfiguredDirection();
	if (state == Stop)
	{
		myStateMaschine->sendEvent("finishedProfile");
		return false;
	}
	else if (steps <= (RAMP_UP + RAMP_STEADY + RAMP_DOWN))
	{
		return true;
	}
	else if (steps > (RAMP_UP + RAMP_STEADY + RAMP_DOWN)) {
		myConveyorBelt->currentMode->motorController->stop();
		myConveyorBelt->currentMode->motorController->resetStepCounter();
		myStateMaschine->sendEvent("finishedProfile");
		return false;
	}
}

bool readyToReceive()
{
	return myConveyorBelt->currentMode->motorController->readyToRecvPayload();

}

//  ACTIONS FOR TESTING
void noAction() {
	// cout << "no action\n" << endl;
}



void noAction1() {
	cout << "\nIdle --> Local" << endl;
	cout << "No action\n" << endl;
	return;
}

void noAction2() {
	cout << "\nFollowProfile --> Local" << endl;
	cout << "No action\n" << endl;
	return;
}

void noAction3() {
	cout << "\nLocal --> Chain" << endl;
	cout << "No action\n" << endl;
	return;
}

void noAction4() {
	cout << "\nIdle --> Chain" << endl;
	cout << "No action\n" << endl;
	return;
}

void noAction5() {
	cout << "\nChain --> Requested" << endl;
	cout << "No action\n" << endl;
	myConveyorBelt->currentMode->communication = ((ChainMode*)(myConveyorBelt->currentMode))->network;

	return;
}

void actionSetSpeed1() {
	cout << "\nLocal --> Local" << endl;
	// motorController->setSpeed(100);		// Woher bekomme ich die Inputs? globale Variablen?
}

void actionSetSpeed2() {
	cout << "\nChain --> Chain" << endl;
	// motorController->setSpeed(200);
}

void actionSetDirection() {
	cout << "\nLocal --> Local" << endl;
	// motorController->setDirection(motorController->direction);
}

void actionFollowProfile1() {
	cout << "\nLocal --> FollowProfile" << endl;
	cout << "Start following profile.\n " << endl;
}

void actionFollowProfile2() {
	cout << "\nReceivingPayload --> FollowProfile" << endl;
	cout << "Start following profile. \n" << endl;
}

void actionSetSpeedAndSteps() {
	cout << "\nFollowProfile --> Local" << endl;
	// myProfile->step++;
	cout << "Set speed and increment steps\n" << endl;;
}

void actionHandleRequest_Wait1() {
	cout << "\nRequested --> Requested" << endl;
	cout << "Handling reqeuest ... sending wait ... \n" << endl;
}

void actionHandleRequest_Wait2() {
	cout << "\nReceivingPayload --> ReceivingPayload" << endl;
	cout << "Handling reqeuest ... sending wait ... \n" << endl;
}

void actionHandleRequest_Wait3() {
	cout << "\nFollowProfile --> FollowProfile" << endl;
	cout << "Handling reqeuest ... sending wait ... \n" << endl;
}

void actionHandleRequest_Wait4() {
	cout << "\nRequesting --> Requesting" << endl;
	cout << "Handling reqeuest ... sending wait ... \n" << endl;
}

void actionHandleRequest_Ready() {
	cout << "\nRequested --> ReceivingPayload" << endl;
	cout << "Handling reqeuest ... sending ready ... \n" << endl;
}

void actionSendRequest() {
	cout << "\nFollowProfile --> Requesting" << endl;
	cout << "Sending request ... \n" << endl;
}

void actionMotorStop1() {
	cout << "\nRequesting --> Requesting" << endl;
	cout << "Motor stopped. \n" << endl;
}

void actionMotorStop2() {
	cout << "\nRequesting --> Requesting" << endl;
	cout << "Motor stopped. \n" << endl;
}

void actionMotorMove() {
	cout << "\nPassLoad --> Chain" << endl;
	cout << "Motor moving slowly ... \n" << endl;
}


// CONDITIONS
//bool noCondition() {
//	return true;
//}

bool conditionTotalSteps() {

	// cout << "Total steps > 400 " << endl;
	//if (myProfile->step >= 400)
	//	return true;
	return false;
}
