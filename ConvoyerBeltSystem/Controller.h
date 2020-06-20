#pragma once

extern "C" {
#include "Discrete_types.h"
#include "Discrete_private.h"
#include "rtwtypes.h"
#include "Discrete.h"     
}

class Controller
{
public:
	Controller();
	~Controller();
	int setValue(double value);
	void oneStep();
};


