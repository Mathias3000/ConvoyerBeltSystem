#include "TestFunctions.h"
#include <cstdio>


void testTCPServer()
{
	TCPServer* server = new TCPServer(inet_addr(HOST_IP), TCP_PORT);

	while (1) {}
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

	while (1) {}
}

void testTelnet()
{
	TelnetServer* telnetServer = new TelnetServer();

	while (1) {}
}

void testTCPClient()
{
	TCPClient* client = new TCPClient(inet_addr(RIGHT_CONVBELT_IP), TCP_PORT);

	while (1){}
}

void testADC() {
	unsigned short readBackValADC = 0;
	int retVal = 0;
	/*
	CH0 - IN - Output from AD223 -> current measurement from Motorcontroller
	CH1 - IN - Output from Poti
	CH2 - Internal Poti (purpose?)
	CH3 - Power_12V (purpose?)
	DOUT -> TXB0104 Levelshifter B1 -> A1 -> SPI0_MISO
	DIN -> SPI0_MOSI
	CS, SCLK - SPI0
	*/

	spiPinmux spiADC;
	spiPinmux& spiADCRef = spiADC;
	strcpy(spiADCRef.CSpin, "P9_17_pinmux");
	strcpy(spiADCRef.MISOpin, "P9_21_pinmux");
	strcpy(spiADCRef.MOSIpin, "P9_18_pinmux");
	strcpy(spiADCRef.SCLKpin, "P9_22_pinmux");

	spiDescriptor* spiDescADC = new spiDescriptor;
	spiDescADC->spiNum = 1;
	spiDescADC->bitsPerWord = 8;
	spiDescADC->mode = 0;
	spiDescADC->flags = O_RDWR;
	spiDescADC->speed = 1000000; 
	spiDescADC->pinmux = spiADCRef;

	retVal = spiSetPinmux(spiDescADC);
	retVal = spiOpen(spiDescADC);

	while (true)
	{
		readBackValADC = spiXfer8Bits(spiDescADC, 0x90); //Channel 1
		readBackValADC = spiXfer16Bits(spiDescADC, 0x0);
		sleep(0.1);
	}
}

void testMotor(int dir)
{
	int retVal = 0;
	unsigned short readBackValSPI = 0;
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
	retVal = gpioGetValue(bridgeDIS);

	spiPinmux spiMotor;
	spiPinmux& spiMotorRef = spiMotor;
	strcpy(spiMotorRef.CSpin, "P9_28_pinmux");
	strcpy(spiMotorRef.MISOpin, "P9_29_pinmux");
	strcpy(spiMotorRef.MOSIpin, "P9_30_pinmux");
	strcpy(spiMotorRef.SCLKpin, "P9_31_pinmux");
	
	spiDescriptor* spiDescMotor = new spiDescriptor;
	spiDescMotor->spiNum = 2;
	spiDescMotor->bitsPerWord = 8;
	spiDescMotor->mode = 1;
	spiDescMotor->flags = O_RDWR;
	spiDescMotor->speed = 1000000; 
	spiDescMotor->pinmux = spiMotorRef;

	retVal = spiSetPinmux(spiDescMotor); //Breakpoint setzen
	retVal = spiOpen(spiDescMotor);

	readBackValSPI = spiXfer16Bits(spiDescMotor, 0xED18);
	usleep(50);
	readBackValSPI = spiXfer16Bits(spiDescMotor, 0x6D18);
	
	/*
	IN1, IN2: Logic input control of OUT1, OUT2
	Code example Pilsan:
	pwmDescriptor* pwm = (pwmDescriptor*)malloc(sizeof(pwmDescriptor));
	strcpy(pwm->pinNameA, "P8_19_pinmux");
	strcpy(pwm->pinNameB, "P8_13_pinmux");
	pwm->pwmNum = 7;
	*/
}

void testKeyBoard()
{
	Keyboard* k = new Keyboard();
	char readValue;

	while (true) {
		readValue = k->getPressedKey();
		cout << "Key pressed: " << readValue << endl;
		this_thread::sleep_for(chrono::milliseconds(150));
	}

}

/*
	myStateMachine->tab[0][0] = new TableEntry ("Local_Idle", "Local_Idle", "command=speed", 0, myAction00, myConditionTrue);
	myStateMachine->tab[0][1] = new TableEntry ("Local_Idle", "Local_Idle", "command=direction", 0, myAction01, myConditionTrue);
	myStateMachine->tab[0][2] = new TableEntry("Local_Idle", "FollowProfile", "command=followProfile", 0, myAction02, myConditionTrue);
	myStateMachine->tab[0][3] = new TableEntry("FollowProfile", "Local_local", "myMotorController.finishedProfile", 0, myAction03, myConditionTrue);
*/

void* testSM(void*)
{	
	Keyboard* k = new Keyboard();
	char readValue;
	while (true)
	{	
		readValue = k->getPressedKey();
		if (readValue == '3') {
			myStateMachine->sendEvent("command=speed");
			readValue = 0;
		}
		else if (readValue == '4') {
			myStateMachine->sendEvent("command=direction");
			readValue = 0;
		}
		else if (readValue == '5') {
			myStateMachine->sendEvent("command=followProfile");
			readValue = 0;
		}
		else if (readValue == '6') {
			myStateMachine->sendEvent("myMotorController.finishedProfile");
			readValue = 0;
		}
		sleep(0.5);
	}
	return NULL;
}
