
#include <string>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include "defines.h"
#include "diaTimer.h"
#include "stateMachine.h"

#define TIMER_SIG SIGRTMAX

static void myTimerHandler(union sigval sv) {
	((DiaTimer*)sv.sival_int)->timerCallback(); // Send event to parent state machine instance
	return;
}

DiaTimer :: DiaTimer(StateMachine * stateMachine) {
	// Create the instance
	myStateMachine = stateMachine; // Assign pointer of parent state machine class
	return;
}

void DiaTimer :: init() {
	struct sigevent sev;
	sev.sigev_value.sival_int = (int)this;
	sev.sigev_notify = SIGEV_THREAD; /* Notify via thread */
	sev.sigev_notify_function = myTimerHandler; /* Thread start function */
	sev.sigev_notify_attributes = NULL;
	if (timer_create (CLOCK_REALTIME, &sev, &myTimer) != 0)
		perror("Timer create");
	return;
}

DiaTimer :: ~DiaTimer() {
	timer_delete (myTimer);
	return;
}

void DiaTimer :: startTimer(int eventTime) {
	struct itimerspec myTimerSpec;
	struct itimerspec oldTimerSpec;
	time_t nSeconds = eventTime/1000;
	long nNanoSeconds = (eventTime % 1000)*1000000;
	myTimerSpec.it_value.tv_sec = nSeconds;
	myTimerSpec.it_value.tv_nsec = nNanoSeconds;
	myTimerSpec.it_interval.tv_sec = 0;
	myTimerSpec.it_interval.tv_nsec = 0;
	timer_settime(myTimer, CLOCK_REALTIME, &myTimerSpec, &oldTimerSpec);
	return;
}

void DiaTimer :: timerCallback () {
	myStateMachine->sendEvent(timerName); // Send event to parent state machine instance
	return;
}
