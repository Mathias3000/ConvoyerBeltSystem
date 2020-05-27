#pragma once

using namespace std;


extern "C" {
#include "Discrete_types.h"
#include "Discrete_private.h"
#include "rtwtypes.h"
#include "Discrete.h"     
}

class Controller
{
public:
	int setValue(double value);

	void oneStep();
};


