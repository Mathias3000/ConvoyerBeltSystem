#include "TCPServer.h"

TCPServer::TCPServer(in_addr_t IPAddress, int port) {

	this->port = port;
	socketAddress = IPAddress;
	//init();
}

TCPServer::TCPServer()
{
	init();
}

TCPServer::~TCPServer()
{
}

void TCPServer::sendData(string data)
{
	// convert string to char*
	char* toSend = new char[data.size() + 1];
	std::copy(data.begin(), data.end(), toSend);
	toSend[data.size()] = '\0'; // don't forget the terminating 0

	send(clientSocket, toSend, strlen(toSend), 0);
	delete[] toSend;
}

int TCPServer::init()
{
	// create a socket
	listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == -1) {
		cerr << "Can't create a socket";
		return -1;
	}
	cout << "Socket created. " << endl;

	// Bind socket to IP address and port
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = socketAddress;	// or INADDR_ANY to use the address of the BB
	server.sin_port = htons(port);			// default set to 5555

	//inet_pton(AF_INET, "0.0.0.0", &server.sin_addr);

	if (bind(listening, (sockaddr*)&server, sizeof(server)) == -1) {
		cerr << "Can't bind to IP/port";
		return -2;
	}

	cout << "Listening to clients" << endl;

	// Mark the socket for listening
	if (listen(listening, SOMAXCONN) == -1) {
		cerr << "Can't listen!" << errno;
		return -3;
	}

	// Start a worker thread for each new connection
	while (true) {

		// Accept a call
		cout << "Accepting clients ... " << endl;
		clientSize = sizeof(client);
		clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
		if (clientSocket == -1) {
			cerr << "Problem with client connetion!";
			return -4;
		}

		// worker thread
		thread* clientThread;
		clientThread = new thread(&TCPServer::threadClientHandler, this);
		// clientThread->join();
	}

	return 0;
}


void TCPServer::threadClientHandler()
{
	cout << "Connected with client" << endl;

	// TODO: Delete Greeting. Only used for debugging
	// Greet Client!
	cout << "Initiate Greeting of client! Code Red!" << endl;
	char greeting[] = "Hi Client! What's up!";
	send(clientSocket, greeting, sizeof(greeting) + 1, 0);
	// int val = write(*(int*)(clientSocket), greeting, sizeof(greeting) + 1);
	// int val = send(*((int*)(clientSocket)), greeting, sizeof(greeting) + 1, 0);
	

	while (true)
	{
		// empty buffer
		memset(buffer, 0, BUF_SIZE);

		// read value and save in buffer
		// read(*((int*)(clientSocket)), buffer, BUF_SIZE);
		recv(clientSocket, buffer, BUF_SIZE, 0);
		
		// handle input from client = LEFT or MASTER
		handleClientInput();

	}

	// cleaning up garbage
	memset(host, 0, NI_MAXHOST);
	memset(svc, 0, NI_MAXSERV);
}

void TCPServer::handleClientInput()
{
	string input(buffer);

	// debug
	cout << "Received from Client (LEFT OR MASTER): " << input << endl;

	// TODO: Check if currentMode == ChainMode
	// Maybe set communication to network when changing to ChainMode: NO, only makes sense if in chainmode only TCP is used
	// myConveyorBelt->currentMode->communication = ((ChainMode*)myConveyorBelt->currentMode)->network;
	
	updateCommunicationType = true;
	if (input == "REQUEST\r\n" || input == "Request\r\n" || input == "request\r\n") {
		myStateMaschine->sendEvent("RecvCmdRequest");
	}
	else if (input == "RELEASE\r\n" || input == "Release\r\n" || input == "release\r\n")
	{
		myStateMaschine->sendEvent("RecvCmdReleased");
	}
	else if (input == "READY\r\n" || input == "Ready\r\n" || input == "ready\r\n")
	{
		myStateMaschine->sendEvent("RecvCmdReady");
	}
	else if (input == "WAIT\r\n" || input == "Wait\r\n" || input == "wait\r\n")
	{
		myStateMaschine->sendEvent("RecvCmdWait");
	}
	else if (input == "tel start\r\n") {
		myStateMaschine->sendEvent("RecvCmdRequest");
	}
	else if (input == "tel stop\r\n")
	{
		myStateMaschine->sendEvent("RecvCmdReleased");
	}
	else if (input == "tel dir right\r\n")
	{
		myStateMaschine->sendEvent("RecvCmdReady");
	}
	else if (input == "tel dir left\r\n")
	{
		myStateMaschine->sendEvent("RecvCmdWait");
	}
	else if (input.find(SPEED_CMD) != string::npos)		// check if speed command string
	{
		string s = input;
		std::string delimiter = ":";

		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			std::cout << token << std::endl;
			s.erase(0, pos + delimiter.length());
		}
		std::cout << s << std::endl;
		speedBuffer = stoi(s);
	}
	else
	{
		updateCommunicationType = false;
	}

}


