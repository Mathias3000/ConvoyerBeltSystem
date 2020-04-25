#include "TCPServer.h"
#include <string.h>

TCPServer::TCPServer(in_addr_t IPAddress, int port) {

	this->port = port;
	socketAddress = IPAddress;
	init();
}

int TCPServer::init() {

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

	// Accept a call
	clientSize = sizeof(client);
	clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	if (clientSocket == -1) {
		cerr << "Problem with client connetion!";
		return -4;
	}

	cout << "Connected with client" << endl;

	// Close socket
	close(listening);

	// Greet Client!
	cout << "Initiate Greeting of client! Code Red!";
	char greeting[] = "Hi Client! What's up!";
	send(clientSocket, greeting, sizeof(greeting) + 1, 0);

	// cleaning up garbage
	memset(host, 0, NI_MAXHOST);
	memset(svc, 0, NI_MAXSERV);

	return 0;

}
