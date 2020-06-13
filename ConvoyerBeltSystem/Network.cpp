#include "Network.h"

Network::Network()
{
	rightConveyorBelt = new TCPClient();
	leftConveyorBelt = new TCPServer();
	master = new TCPServer();
}

Command* Network::parse()
{
	return nullptr;
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
