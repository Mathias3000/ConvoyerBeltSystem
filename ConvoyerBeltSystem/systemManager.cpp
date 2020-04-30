
#include "stateTable.h"
#include "systemManager.h"
#include "stateMachine.h"
#include "keyboard.h"
#include "myFunctions.h"

int n, m;
StateMachine * myStateMachine;
Keyboard* myKeyboard;

SystemManager :: SystemManager() {
	// Create the instance
	return;
}

void SystemManager ::init() {

	// Create instance of state machine
	myStateMachine = new StateMachine;

	// Initialize table for all diagrams, event time in ms
	// The maximum size of the table is defined in defines.h:
	// MAXDIA = 9, MAXLINES = 66
	// Should these be exceeded, please correct!

	/*
	1. Arraywith states, events and actions showing what shallhappen:Entry[i]: 
	actState -nextState -event -time -action -conditionEach diagram has one array. 
	For each event there is one entry if the event has no conditions. 
	Otherwise there can be n entries, depending on the number of conditions. 
	If a condition evaluates to TRUE, the transition is taken. If no condition is needed,then condition shall beTRUE! 
	The term „time“is only needed if the event is a timer.The time is to bespecified in ms.Data types: actState, nextState, event = C++-string; 
	action, condition = function pointer; time = int.
	*/

	//Local Mode: Actions noch umbenennen, ...
	myStateMachine->tab[0][0] = new TableEntry ("Local_Idle", "Local_Idle", "command=speed", 0, myAction00, myConditionTrue);
	myStateMachine->tab[0][1] = new TableEntry ("Local_Idle", "Local_Idle", "command=direction", 0, myAction01, myConditionTrue);	
	myStateMachine->tab[0][2] = new TableEntry("Local_Idle", "FollowProfile", "command=followProfile", 0, myAction02, myConditionTrue);
	myStateMachine->tab[0][3] = new TableEntry("FollowProfile", "Local_Idle", "myMotorController.finishedProfile", 0, myAction03, myConditionTrue);

	//Chain Mode:
	myStateMachine->tab[1][0] = new TableEntry ("Chain_Idle", "Chain_Idle", "Set speed", 0, myAction10, myConditionTrue);
	myStateMachine->tab[1][1] = new TableEntry ("Chain_Idle", "Requested", "Request from left", 0, myAction11, myConditionTrue);
	myStateMachine->tab[1][2] = new TableEntry ("Requested", "Requested", "Timer1", 4000, myAction12, myCondition12);
	myStateMachine->tab[1][3] = new TableEntry ("StateE", "StateC", "Timer1", 3000, myAction13, myConditionTrue);

	//Follow Profile
	myStateMachine->tab[2][0] = new TableEntry ("Chain_Idle","Chain_Idle","Trigg1",0,myAction20,myConditionTrue);

	// Initialize timer names for all diagrams
	// Timer names shall have the name Timer followed by the diagram number
	myStateMachine->timerNames[0] = "Timer0";
	myStateMachine->timerNames[1] = "Timer1";
	myStateMachine->timerNames[2] = "Timer2";

	// Initialize line numbers for all diagrams
	myStateMachine->lines[0] = 4;
	myStateMachine->lines[1] = 0;
	myStateMachine->lines[2] = 0;

	// Initialize first state for all diagrams
	myStateMachine->actualState[0] = "Local_Idle";
	myStateMachine->actualState[1] = "StateC";
	myStateMachine->actualState[2] = "StateK";
	
	// Set the actual number of diagrams
	myStateMachine->diagrams = 1;

	// Initialize state machine
	myStateMachine->init();
	
	// Start timer for each diagram which needs one in the first state!
	// In my case these are diagram 0 and 2
	/*
	myStateMachine->diaTimerTable[0]->startTimer(myStateMachine->tab[0][0]->eventTime);
	myStateMachine->diaTimerTable[2]->startTimer(myStateMachine->tab[2][0]->eventTime);
	*/

	// Initial actions can be done here, if needed!
	n = 0;
	m = 0;

	// Create instance of my Keyboard
	//myKeyboard = new Keyboard;

	return;
}

SystemManager :: ~SystemManager() {
	return;
}

void SystemManager :: startStateMachine() {
	// Start the state machine. This method blocks, so no while(1) is needed.
	myStateMachine->runToCompletion();
	return;
}

void myAction00() {
	printf(" Local_Idle -> Transition00 -> Local_Idle\n");
	return;
}

void myAction01() {
	printf(" Local_Idle -> Transition01 -> Local_Idle\n"); 
	return;
}

void myAction02() {
	printf(" Local_Idle -> Transition02 -> FollowProfile\n"); 
	return;
}

void myAction03() {
	printf(" FollowProfile -> Transition03 -> Local_Idle\n");
	return;
}

void myAction10() {
	printf(" StateC -> Transition10 -> StateD\n"); 
	m = 0;
	return;
}

void myAction11() {
	printf(" StateD -> Transition11 -> StateD\n"); 
	m++;
	return;
}

void myAction12() {
	printf(" StateD -> Transition12 -> StateE\n"); 
	return;
}

void myAction13() {
	printf(" StateE -> Transition13 -> StateC\n"); 
	myStateMachine->sendEvent("Trigg0");
	return;
}

void myAction20() {
	myKeyboard->getPressedKey();
	return;
}

bool myConditionTrue() {
	return true;
}

bool myCondition00() {
	if (n < 5) {
		return true;
	}
	else return false;
}

bool myCondition01() {
	if (n >= 5) return true;
	else return false;
}

bool myCondition11() {
	if (m < 4) return true;
	else return false;
}

bool myCondition12() {
	if (m >= 4) return true;
	else return false;
}

