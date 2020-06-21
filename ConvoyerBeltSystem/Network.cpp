#include "Network.h"

Network::Network()
{
	rightConveyorBelt = new TCPClient();
	leftConveyorBelt = new TCPServer(HOST_IP, TCP_PORT);
	master = new TCPServer(CONVBELT_IP, TCP_PORT);

}

Network* Network::getInstance()
{
	if (instance == NULL) {
		instance = new Network();
	}
	return instance;
}

Command* Network::parse()
{
	Command* receivedCommand;
	// only reading values from left system: in order to track number of current request in the queue
	receivedCommand = new Command(to_string(leftConveyorBelt->requestBuffer), SystemLocation::LeftConveyorBelt, Self);	
	leftConveyorBelt->requestBuffer--;

	return receivedCommand;
}

void Network::send(string data, SystemLocation src, SystemLocation dest)
{
	switch (dest)
	{
	case RightConveyorBelt:
		// Concat src and dest to string: define protocol: IS THAT REALLY NEEDED? 
		rightConveyorBelt->sendData(data);
		break;
	case LeftConveyorBelt:
		leftConveyorBelt->sendData(data);
		break;
	case Master:
		master->sendData(data);
		break;
	default:
		break;
	}
}

void Network::send(string data, SystemLocation dest)
{
	switch (dest)
	{
	case RightConveyorBelt:
		// Concat src and dest to string: define protocol: IS THAT REALLY NEEDED? 
		rightConveyorBelt->sendData(data);
		break;
	case LeftConveyorBelt:
		leftConveyorBelt->sendData(data);
		break;
	case Master:
		master->sendData(data);
		break;
	default:
		break;
	}
}
