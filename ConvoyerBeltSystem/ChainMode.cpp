#include "ChainMode.h"

ChainMode::ChainMode():Mode()
{
	network = new Network();
}

Command* ChainMode::recv()
{
	Command* recvData = network->parse();
}

void ChainMode::send(Command* command)
{
	network->send(command->data, command->dest);
}
