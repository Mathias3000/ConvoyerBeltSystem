#include "TCPClient.h"

TCPClient::TCPClient(in_addr_t IPAddress, int port)
{
    this->IPAddress = IPAddress;
    this->port = port;
    init();
}

int TCPClient::init()
{

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cerr << "Socket creation error " << endl;
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(TCP_PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form 
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0)
    {
        cerr << "Invalid address/ Address not supported " << endl;
        return -2;
    }

    if (connect(sock, (struct sockaddr*) & serverAddr, sizeof(serverAddr)) < 0)
    {
        cerr << "Connection Failed " << endl;
        return -3;
    }

    send(sock, test, strlen(test), 0);
    cout << "Sent message to Server" << endl;

}
