#include "TestFunctions.h"

void testTCPServer()
{
	TCPServer* server = new TCPServer(inet_addr(CONVBELT_IP), TCP_PORT);

	while (1) {

	}
}

void testDisplay()
{
	Display* d = new Display();

	int motorNumber1 = 1;
	int motorNumber2 = 2;
	double speed1 = 200.455;
	double speed2 = 300.595;

	// HEADLINE
	d->displayLine("MOTOR SPEEDS");
	d->displayLine("");	// used as line feed

	// speed motor 1
	d->display("Speed of motor ");
	d->display(motorNumber1);
	d->display(": ");
	d->display(speed1);
	d->displayLine(" rms! ");

	// speed motor 1
	d->display("Speed of motor ");
	d->display(motorNumber2);
	d->display(": ");
	d->display(speed2);
	d->displayLine(" rms! ");

	while (1) {

	}
}

void testTelnet()
{
	TelnetServer* telnetServer = new TelnetServer();

	while (1) {

	}
}
