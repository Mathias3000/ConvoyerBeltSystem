#include "LocalMode.h"

LocalMode::LocalMode():Mode()
{
}

LocalMode::~LocalMode()
{
	delete this;
}

Command* LocalMode::recv()
{
}

