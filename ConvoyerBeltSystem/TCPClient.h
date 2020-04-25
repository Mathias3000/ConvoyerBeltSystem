#pragma once
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <string.h>

#define RIGHT_CONVBELT_IP "192.168.7.1"
#define TCP_PORT 5555
#define BUF_SIZE 128

using namespace std;

class TCPClient
{
private: 
	int sock;
	char buffer[BUF_SIZE];
	sockaddr_in serverAddr;
	char* test = "Hello from Client";
	in_addr_t IPAddress;
	int port;

public: 
	TCPClient(in_addr_t serverAddress, int port);
	int init();


};

