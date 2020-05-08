#include "SpeedProfile.h"

int SpeedProfile::incrementStepCounter()
{
	this->stepCounterFollowProf += 1;
	return this->stepCounterFollowProf;
}

int SpeedProfile::getStepCounter()
{
	return this->stepCounterFollowProf;
}

int SpeedProfile::resetStepCounter()
{
	this->stepCounterFollowProf = 0;
	return 0;
}
