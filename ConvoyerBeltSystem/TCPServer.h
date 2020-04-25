#pragma once
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

#define HOST_IP "192.168.7.2"			// telnet
#define CONVBELT_IP "91.0.0.7"			// tcp

#define TCP_PORT 5555
#define TELNET_PORT 4444

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
	int buffersize = 128;
	char buffer[];

	int init();

public: 
	TCPServer(in_addr_t IPAddress, int port);
	~TCPServer();
	char* recv();


};

