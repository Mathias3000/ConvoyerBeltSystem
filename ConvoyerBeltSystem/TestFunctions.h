#pragma once
#include <string>
#include "TCPServer.h"
#include "Display.h"
#include "TelnetServer.h"

using namespace std;

// Should be implemented: Maybe try TDD (test driven development)
void testTCPServer();		// test with socketTest tool
void testDisplay();
void testTelnet();			// test with CMD line: telnet 192.168.7.2 4444
void testKeyPad();
void testPotentiometer();
void testMotor();


