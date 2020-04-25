#pragma once
#include <string>
#include "TCPServer.h"
#include "Display.h"
#include "TelnetServer.h"

using namespace std;

// Should be implemented: Maybe try TDD (test driven development)
void testTCPServer();
void testDisplay();
void testTelnet();	// test with putty: connect with telnet port 23 & IP adress
void testKeyPad();
void testPotentiometer();
void testMotor();


