#include "Command.h"

Command::Command(string data, SystemLocation src, SystemLocation dest)
{
	this->data = data;
	this->src = src;
	this->dest = dest;
}

Command::Command(string data, SystemLocation dest)
{
	this->data = data;
	this->dest = dest;
	this->src = NoLocation;
}

Command::Command()
{
	// init values
	this->data = "";
	this->src = NoLocation;
	this->dest = NoLocation;
}

Command::~Command()
{
	delete this;
}
