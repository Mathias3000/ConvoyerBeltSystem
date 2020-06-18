#pragma once

class SpeedProfile
{
public:
	int step;
	SpeedProfile();
	int getStatus();
	int startProfile(bool direction);
	int incrementStepCounter();
	int getStepCounter();
	int resetStepCounter();
private:
	int stepCounterFollowProf = 0;
};

