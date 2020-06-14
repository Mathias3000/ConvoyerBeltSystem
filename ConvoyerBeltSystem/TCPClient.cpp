#include "TCPClient.h"

TCPClient::TCPClient(in_addr_t serverAddress, int port)
{
    this->IPAddress = IPAddress;
    this->port = port;
    init();
}

TCPClient::TCPClient()
{
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

    // create worker thread
    while (true) {

        if (connect(sock, (struct sockaddr*) & serverAddr, sizeof(serverAddr)) < 0)
        {
            cerr << "Connection Failed " << endl;
            return -3;
        }

        thread* serverThread;
        serverThread = new thread(&TCPClient::threadServerHandler, this);
        serverThread->join();

    }

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cerr << "Connection Failed " << endl;
        return -3;
    }

    send(sock, test, strlen(test), 0);
    cout << "Sent message to Server" << endl;

}

void TCPClient::sendData(string data)
{
    // convert string to char*
    char* toSend = new char[data.size() + 1];
    std::copy(data.begin(), data.end(), toSend);
    toSend[data.size()] = '\0'; // don't forget the terminating 0

    send(sock, toSend, strlen(toSend), 0);
    delete[] toSend;
}

void TCPClient::threadServerHandler()
{
}


