#include "ChainMode.h"

ChainMode::ChainMode():Mode()
{
	network = new Network();
}

ChainMode* ChainMode::getInstance()
{
	if (instance == NULL) {
		instance = new ChainMode();
	}
	return instance;
}

Command* ChainMode::recv()
{
	Command* recvData = network->parse();
}

void ChainMode::send(Command* command)
{
	network->send(command->data, command->dest);
}
