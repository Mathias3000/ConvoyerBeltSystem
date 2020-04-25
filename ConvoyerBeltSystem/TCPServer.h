#pragma once
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

using namespace std;

class TCPServer
{
private: 

	int port = 5555;	// default
	in_addr_t systemAddr = inet_addr("192.168.7.2");
	in_addr_t convBeltAddr = inet_addr("91.0.0.7");

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
	TCPServer(int port);
	~TCPServer();
	char* recv();


};

