#pragma once
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <thread>
#include <string.h>
#include "stateMachine.h"

#define HOST_IP "192.168.7.2"			// telnet
#define CONVBELT_IP "91.0.0.7"			// tcp

#define TCP_PORT 5555
#define TELNET_PORT 4444

#define BUF_SIZE 128

#define SPEED_CMD "tel speed"


using namespace std;

class TCPServer
{
private: 

	int port = TCP_PORT;	// default
	in_addr_t socketAddress = inet_addr(HOST_IP);	// default

	int listening;
	sockaddr_in server;
	sockaddr_in client;
	socklen_t clientSize;
	char host[NI_MAXHOST];
	char svc[NI_MAXSERV];	// services
	int clientSocket;

	int init();

public: 
	char buffer[BUF_SIZE];
	bool updateCommunicationType = false;
	int speedBuffer = 0;

	TCPServer(in_addr_t IPAddress, int port);
	TCPServer();
	~TCPServer();
	void sendData(string data);
	void threadClientHandler();
	void handleClientInput();

};

