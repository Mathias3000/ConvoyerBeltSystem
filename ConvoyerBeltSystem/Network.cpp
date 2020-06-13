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

void Network::send(string data, Destination destination)
{
	switch (destination)
	{
	case Network::LeftConveyorBelt:
		leftConveyorBelt->sendData(data);
		break;
	case Network::RightConveyorBelt:
		rightConveyorBelt->sendData(data);
		break;
	case Network::Master:
		master->sendData(data);
		break;
	default:
		break;
	}
}
