#include "TestFunctions.h"
#include <cstdio>

void testTCPServer()
{
	TCPServer* server = new TCPServer();

	while (1) {

	}
}

void testMotor(int dir)
{
	/*
	Connection information:
	H-bridge pin IN1 is tied to pwm7 pin A (P8_19).
	H-bridge pin IN2 is tied to pwm7 pin B (P8_13).
	H-bridge pin DIS is tied to GPIO2_12 (P8_39) = 76 (GPIO SW-number).
	H-bridge pin ENBL is tied to GPIO2_15 (P8_38) = 79 (GPIO SW-number).
	*/
	/*
	When ENBL is logic HIGH, the H-Bridge is operational.When ENBL is logic LOW, the H-Bridge outputs are tri-stated and placed in Sleep mode.
	*/
	int retVal = 0;
	unsigned short readBackValSPI = 0;

	gpioDescriptor* bridgeEN = new gpioDescriptor; //(gpioDescriptor*)malloc(sizeof(gpioDescriptor));
	bridgeEN->gpioNum = 79;
	strcpy(bridgeEN->direction, "out");
	/*
	When DIS is logic HIGH, both OUT1 and OUT2 are tri-stated
	*/
	gpioDescriptor* bridgeDIS = new gpioDescriptor;
	bridgeDIS->gpioNum = 76;
	strcpy(bridgeDIS->direction, "out");

	gpioOpen(bridgeEN);
	retVal = gpioSetValue(bridgeEN, 1);
	gpioOpen(bridgeDIS);
	retVal = gpioSetValue(bridgeDIS, 0);

	retVal = gpioGetValue(bridgeEN);

	spiPinmux spiMotor;
	spiPinmux& spiMotorRef = spiMotor;
	strcpy(spiMotorRef.CSpin, "P9_28_pinmux");
	strcpy(spiMotorRef.MISOpin, "P9_29_pinmux");
	strcpy(spiMotorRef.MOSIpin, "P9_30_pinmux");
	strcpy(spiMotorRef.SCLKpin, "P9_31_pinmux");
	/*
	strcpy(spiMotor->CSpin, "P9_28_pinmux");
	strcpy(spiMotor->MISOpin, "P9_29_pinmux");
	strcpy(spiMotor->MOSIpin, "P9_30_pinmux");
	strcpy(spiMotor->SCLKpin, "P9_31_pinmux");
	*/
	spiDescriptor* spiDescMotor = new spiDescriptor;
	spiDescMotor->spiNum = 2;
	spiDescMotor->bitsPerWord = 8;
	spiDescMotor->mode = 1;
	spiDescMotor->flags = 2;
	spiDescMotor->speed = 10e6; // ???...
	spiDescMotor->pinmux = spiMotor;

	retVal = spiSetPinmux(spiDescMotor);
	retVal = spiOpen(spiDescMotor);
	
	//readBackValSPI = spiXfer16Bits(spiDescMotor, 0x0);
	readBackValSPI = spiXfer16Bits(spiDescMotor, 0xFD98);
	readBackValSPI = spiXfer16Bits(spiDescMotor, 0x7D98);
	while (true);

	/*
	IN1, IN2: Logic input control of OUT1, OUT2
	Code example Pilsan:
	pwmDescriptor* pwm = (pwmDescriptor*)malloc(sizeof(pwmDescriptor));
	strcpy(pwm->pinNameA, "P8_19_pinmux");
	strcpy(pwm->pinNameB, "P8_13_pinmux");
	pwm->pwmNum = 7;
	*/
}
