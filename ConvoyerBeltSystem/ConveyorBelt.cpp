#include "ConveyorBelt.h"

ConveyorBelt::ConveyorBelt()
{
	currentMode = new LocalMode();
}

ConveyorBelt::~ConveyorBelt()
{
	delete this;
}
