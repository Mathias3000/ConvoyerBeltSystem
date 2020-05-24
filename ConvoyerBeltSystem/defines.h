#pragma once

#ifndef DEFINES_H_
#define DEFINES_H_

#define MAXDIA 9
#define MAXLINES 66
#define MAX_STATE_NAME 20
#define RAMP_UP 50
#define RAMP_STEADY 350
#define RAMP_DOWN 50
#define PWM_PER 50000
#define MAX_SPEED 100

#define ENC_TICKS_PER_TURN 2000
#define DEG_PER_TICK 0.18
#define ENC_DELAY_SEC 0.02
#define ENC_DELAY_USEC 20000
#define ENC_DEALY_NSEC 20000000

typedef enum
{
	Right, Left
} Direction;

typedef enum 
{
	 movingRight, movingLeft, Stop
} MotorState;

#endif // DEFINES_H_
