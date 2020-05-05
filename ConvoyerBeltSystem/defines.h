#pragma once

#ifndef DEFINES_H_
#define DEFINES_H_

#define MAXDIA 9
#define MAXLINES 66
#define MAX_STATE_NAME 20
#define RAMP_UP 50
#define RAMP_STEADY 350
#define RAMP_DOWN 400
#define PWM_PER 50000
#define MAX_SPEED 100

typedef enum
{
	Right, Left
} Direction;

#endif // DEFINES_H_
