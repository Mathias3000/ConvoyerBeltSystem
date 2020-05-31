#include "Helpers.h"

void sleep(int milliseconds) {

	double seconds = milliseconds / 1000;
	clock_t startClock = clock();
	double secondsAhead = seconds * CLOCKS_PER_SEC;

	while (clock() < startClock + secondsAhead) {

	}

	return;
}