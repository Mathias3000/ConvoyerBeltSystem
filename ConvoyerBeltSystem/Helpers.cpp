#include "Helpers.h"

void sleep(int milliseconds) {

	double seconds = milliseconds / 1000;
	clock_t startClock = clock();
	double secondsAhead = seconds * CLOCKS_PER_SEC;

	while (clock() < startClock + secondsAhead) {

	}

	return;
}

char* stringToCharArray(string* str)
{
	char* writable = new char[str->size() + 1];
	std::copy(str->begin(), str->end(), writable);
	writable[str->size()] = '\0'; // don't forget the terminating 0
	return writable;
}
