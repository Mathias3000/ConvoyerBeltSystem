
#ifndef DIATIMER_H_
#define DIATIMER_H_

#include <string>

class StateMachine;

class DiaTimer {
public:
	DiaTimer(StateMachine * stateMachine);
	~DiaTimer();
	void init();
	void startTimer(int eventTime);
	void timerCallback (); 
	std::string timerName;
private:
	StateMachine * myStateMachine;
	timer_t myTimer;
//	struct itimerspec myTimerSpec;
};

#endif // DIATIMER_H_
