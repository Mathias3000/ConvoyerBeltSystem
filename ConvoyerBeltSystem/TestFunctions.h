#pragma once
#include <string>
#include <string.h>
#include "TCPServer.h"
extern "C" {
	#include <gpio.h>
	#include <spi.h>
	#include <pwm.h>
}



using namespace std;

// Should be implemented: Maybe try TDD (test driven development)
void testTCPServer();
void testKeyPad();
void testPotentiometer();
void testMotor(int dir);


