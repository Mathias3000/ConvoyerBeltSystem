#include "TCPClient.h"

TCPClient::TCPClient(in_addr_t serverAddress, int port)
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
    bzero(&serverAddr, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(RIGHT_CONVBELT_IP);
    serverAddr.sin_port = htons(TCP_PORT);

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cerr << "Connection Failed " << endl;
        return -3;
    }

    send(sock, test, strlen(test), 0);
    cout << "Sent message to Server" << endl;

}
