#include "Network.h"

Network::Network()
{
	rightConveyorBelt = new TCPClient();
	leftConveyorBelt = new TCPServer();
	master = new TCPServer();
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

	if (rightConveyorBelt->updateCommunicationType) {
		receivedCommand = new Command(rightConveyorBelt->buffer, RightConveyorBelt, Self);
	}
	else if (leftConveyorBelt->updateCommunicationType) {
		receivedCommand = new Command(leftConveyorBelt->buffer, LeftConveyorBelt, Self);
	}
	else if (master->updateCommunicationType) {
		receivedCommand = new Command(master->buffer, Master, Self);
	}
	else {
		receivedCommand = new Command("", NoLocation, NoLocation);
	}
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
