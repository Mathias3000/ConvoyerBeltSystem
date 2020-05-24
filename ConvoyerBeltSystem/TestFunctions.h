#pragma once
#include <string>
#include <string.h>
#include <chrono>
#include <thread>

#include "TCPServer.h"
#include "Display.h"
#include "TelnetServer.h"
#include "TCPClient.h"
#include "systemManager.h"

#include <cstdio>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

//#include "gpio.h"
//#include "spi.h"
//#include "pwm.h"


extern "C" {
#include "gpio.h"
#include "spi.h"
#include "pwm.h"
}

extern Keyboard* k;

using namespace std;

// Should be implemented: Maybe try TDD (test driven development)
void testTCPServer();		// test with socketTest tool: address 192.168.7.2 with port 5555
void testDisplay();			// shows some possible output of motor state
void testTelnet();			// test with CMD line: telnet 192.168.7.2 4444
void testTCPClient();		// test with socketTest tool: listen to 192.168.7.1 address with port 5555
void testKeyPad();
void testPotentiometer();
void testMotor(int dir);

void testADC();
void testKeyBoard();
void testSM();
void testQEP();
void testKeyBoard();

void testADC();
void testKeyBoard();




