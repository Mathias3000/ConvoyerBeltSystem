#pragma once
#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;

extern "C" {
#include "cons.h"
};

class Display
{
public:
	// temp solution
	int display(string string);
	int displayLine(string string);	// with carriage return
	int display(int integerValue); 
	int display(double doubleValue);

	Display();
	~Display();
	int displayLine(char* string);
	int displayClear();
private:
	char myConsoleName[MAX_FILENAME] = "ConveyorBeltConsole";
	consDescriptor* myConsole;
};

