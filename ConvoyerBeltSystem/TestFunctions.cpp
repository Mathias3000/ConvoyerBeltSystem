#include "TestFunctions.h"

void testTCPServer()
{
	int port = 5555;
	TCPServer* server = new TCPServer(port);

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
