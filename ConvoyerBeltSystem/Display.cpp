#include "Display.h"


Display::Display()
{
	printf("Display Construktor!\n");
	this->myConsole = new consDescriptor;
	strncpy(myConsole->fileName, this->myConsoleName, MAX_FILENAME);
	openConsole(myConsole);
};

int Display::displayLine(char* string)
{
	if(writeLineToConsole(this->myConsole, string) < 0) return -1;
	return 0;
};



