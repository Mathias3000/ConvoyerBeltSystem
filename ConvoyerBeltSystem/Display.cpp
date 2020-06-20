#include "Display.h"

int Display::display(string string)
{
	cout << string;
	cout.flush();
	return 0;
}

int Display::displayLine(string string)
{
	cout << string << endl;
	return 0;
}

int Display::display(int integerValue)
{
	cout << integerValue;
	cout.flush();
	return 0;
}

int Display::display(double doubleValue)
{
	cout << doubleValue;
	cout.flush();
	return 0;
}


Display::Display()
{
	printf("Display Construktor!\n");
	this->myConsole = new consDescriptor;
	strncpy(myConsole->fileName, this->myConsoleName, MAX_FILENAME);
	openConsole(myConsole);
}

Display::~Display()
{
	closeConsole(this->myConsole);
	delete this;
}

int Display::displayLine(char* string)
{
	if (writeLineToConsole(this->myConsole, string) < 0) return -1;
	return 0;
}

int Display::displayClear()
{
	if (clearConsole(this->myConsole) < 0) return -1;
	return 0;
}