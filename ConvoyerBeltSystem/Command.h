#pragma once
#include <string>
#include "SystemLocation.h"

using namespace std;

class Command
{
private: 


public: 

	string data;
	SystemLocation src;		// use src for recv function: it can determined, where it came from: RIGHT or LEFT
	SystemLocation dest;

	Command(string data, SystemLocation src, SystemLocation dest);
	Command(string data, SystemLocation dest);
	Command();
	~Command();
};


