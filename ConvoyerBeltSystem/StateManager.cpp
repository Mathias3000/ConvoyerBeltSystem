#include "StateManager.h"

// I need these global variables so that I can access them in my global action functions
// Tip: use prefix "my" for testing with global variables


int n, m;		
Keyboard* myKeyBoard;
StateMachine* myStateMaschine;

MotorController* motorController;
mutex mtxKeys;

// temp global variable for communcation
// maybe this can be avoid. Need to check 
TelnetServer* telnetServer = new TelnetServer();
TCPServer* tcpServer = new TCPServer();
TCPClient* tcpClient = new TCPClient();

StateManager::StateManager()
{
	myKeyBoard = new Keyboard();
	myStateMaschine = new StateMachine();
	encoder = new Encoder();
	controller = new Controller();
	motor = new Motor(encoder, controller);
	speedProfile = new SpeedProfile();
	motorController = new MotorController(motor, speedProfile);
	init();		// init seperat ausführen. Anscheinend kann es zu unbekannten Fehlern führen, wenn man es im ctor ausführt
}

StateManager::~StateManager()
{
	delete this;
}

void StateManager::init()
{
	// Define state charts
	// Local Mode Chart
	myStateMaschine->tab[0][0] = new TableEntry("Idle", "Local", "RecvCmdLocal", 0, noAction1, noCondition);
	myStateMaschine->tab[0][1] = new TableEntry("Local", "Local", "RecvCmdSpeed", 0, actionSetSpeed1, noCondition);
	myStateMaschine->tab[0][2] = new TableEntry("Local", "Local", "RecvCmdDirection", 0, actionSetDirection, noCondition);
	myStateMaschine->tab[0][3] = new TableEntry("Local", "FollowProfile", "RecvCmdFollowProfile", 0, actionFollowProfile1, noCondition);
	myStateMaschine->tab[0][4] = new TableEntry("FollowProfile", "Local", "motorControllerFinishedProfile", 0, noAction2, noCondition);
	myStateMaschine->tab[0][5] = new TableEntry("Local", "Chain", "RecvCmdChain", 0, noAction3, noCondition);

	// FollowProfile Chart: funktioniert so nicht ... lieber als zusätzliche Line jeweils in Local und Chain einbauen
	myStateMaschine->tab[1][0] = new TableEntry("FollowProfile", "Local", "Timer0", 20, actionSetSpeedAndSteps, conditionTotalSteps);		// put timer.start() to different actionFunction

	// Chain Chart
	myStateMaschine->tab[2][0] = new TableEntry("Idle", "Chain", "RecvCmdChain", 0, noAction4, noCondition);
	myStateMaschine->tab[2][1] = new TableEntry("Chain", "Chain", "RecvCmdSpeed", 0, actionSetSpeed2, noCondition);
	myStateMaschine->tab[2][2] = new TableEntry("Chain", "Requested", "RecvCmdRequest", 0, noAction5, noCondition);
	myStateMaschine->tab[2][3] = new TableEntry("Requested", "Requested", "RecvCmdRequest", 0, actionHandleRequest_Wait1, noCondition);
	myStateMaschine->tab[2][4] = new TableEntry("Requested", "ReceivingPayload", "motorControllerReadyToRecvPayload", 0, actionHandleRequest_Ready, noCondition);
	myStateMaschine->tab[2][5] = new TableEntry("ReceivingPayload", "ReceivingPayload", "RecvCmdRequest", 0, actionHandleRequest_Wait2, noCondition);
	myStateMaschine->tab[2][6] = new TableEntry("ReceivingPayload", "FollowProfile", "SendRelease", 0, actionFollowProfile2, noCondition);
	myStateMaschine->tab[2][7] = new TableEntry("FollowProfile", "FollowProfile", "RecvCmdRequest", 0, actionHandleRequest_Wait3, noCondition);
	myStateMaschine->tab[2][8] = new TableEntry("FollowProfile", "Requesting", "motorControllerFinishedProfile", 0, actionSendRequest, noCondition);
	myStateMaschine->tab[2][9] = new TableEntry("Requesting", "Requesting", "RecvCmdRequest", 0, actionHandleRequest_Wait4, noCondition);
	myStateMaschine->tab[2][10] = new TableEntry("Requesting", "Requesting", "RecvCmdWait", 0, actionMotorStop1, noCondition);
	myStateMaschine->tab[2][11] = new TableEntry("Requesting", "PassLoad", "RecvCmdReady", 0, actionMotorMove, noCondition);
	myStateMaschine->tab[2][12] = new TableEntry("PassLoad", "Chain", "RecvCmdRelease", 0, actionMotorStop2, noCondition);

	// Potentiometer/Keyboard Chart for Polling
	// every 50ms check if poti value has changed "significantly"; If it has -> sendEvent for changing speed
	// OR: define Key to accept/validate the chosen value of poti -> But this action can be called in each state of 

	// Display Chart for visualization
	// Get currect state 
	// OR: just print it out continuousyl

	// TCP Server/Client: They send Event when they reveive something. No need for polling. 
	// Example: Telnet Server
	// - receives data
	// - unpack
	// - set global variables?
	// - sendEvent to the queue


	// Initialize timer names for all diagrams
	myStateMaschine->timerNames[0] = "Timer0";

	// Initialize line numbers for all diagrams
	myStateMaschine->lines[0] = 6;	// Anzahl der Teilen bei den Tabellen oben
	myStateMaschine->lines[1] = 1;
	myStateMaschine->lines[2] = 13;

	// Initialize first state for all diagrams
	myStateMaschine->actualState[0] = "Idle";
	myStateMaschine->actualState[1] = "FollowProfile";
	myStateMaschine->actualState[2] = "Idle";

	// Set the actual number of diagrams
	myStateMaschine->diagrams = 3;

	// Initialize state machine
	myStateMaschine->init();

	// Start timer for each diagram which needs one in the first state!
	// In my case these are diagram 0 and 2
	myStateMaschine->diaTimerTable[0]->startTimer(myStateMaschine->tab[1][0]->eventTime);

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


// Function for reading keyInputs
void readKeyInputs()
{
	char readKey;

	while (true) {

		readKey = myKeyBoard->getPressedKey();
		sleep(100);

		// Evaluate
		// -- Events		
		// [1] RecvCmdLocal
		// [2] RecvCmdSpeed
		// [3] RecvCmdDirection
		// [4] RecvCmdFollowProfile
		// [5] motorControllerFinishedProfile
		// [6] RecvCmdChain
		// [7] RecvCmdRequest
		// [8] motorControllerReadToRecvPayload
		// [9] SendRelease
		// [0] motorControllerFinishedProfile
		// [A] RecvCmdWait
		// [B] RecvCmdReady
		// [C] RecvCmdRelease


		// mtxKeys.lock();
		switch (readKey)
		{
		case '0':
			myStateMaschine->sendEvent("motorControllerFinishedProfile");
			break;
		case '1':
			myStateMaschine->sendEvent("RecvCmdLocal");
			break;
		case '2':
			myStateMaschine->sendEvent("RecvCmdSpeed");
			break;
		case '3':
			myStateMaschine->sendEvent("RecvCmdDirection");
			break;
		case '4':
			myStateMaschine->sendEvent("RecvCmdFollowProfile");
			break;
		case '5':
			myStateMaschine->sendEvent("motorControllerFinishedProfile");
			break;
		case '6':
			myStateMaschine->sendEvent("RecvCmdChain");
			break;
		case '7':
			myStateMaschine->sendEvent("RecvCmdRequest");
			break;
		case '8':
			myStateMaschine->sendEvent("motorControllerReadyToRecvPayload");
			break;
		case '9':
			myStateMaschine->sendEvent("SendRelease");
			break;
		case 'A':
			myStateMaschine->sendEvent("RecvCmdWait");
			break;
		case 'B':
			myStateMaschine->sendEvent("RecvCmdReady");
			break;
		case 'C':
			myStateMaschine->sendEvent("RecvCmdReleased");
			break;

		default:
			break;
		}
		// mtxKeys.unlock();
	}

}



// Defining global functions
// ACTIONS
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
	return;
}

void actionSetSpeed1() {
	cout << "\nLocal --> Local" << endl;
	motorController->setSpeed(100);		// Woher bekomme ich die Inputs? globale Variablen?
}

void actionSetSpeed2() {
	cout << "\nChain --> Chain" << endl;
	motorController->setSpeed(200);
}

void actionSetDirection() {
	cout << "\nLocal --> Local" << endl;
	motorController->setDirection(motorController->direction);
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
bool noCondition() {
	return true;
}

bool conditionTotalSteps() {

	// cout << "Total steps > 400 " << endl;
	//if (myProfile->step >= 400)
	//	return true;
	return false;
}
