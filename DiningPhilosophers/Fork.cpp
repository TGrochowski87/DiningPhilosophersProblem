#include "Fork.h"

Fork::Fork(int priority)
{
	this->priority = priority;
}

int Fork::getPriority()
{
	return this->priority;
}

bool Fork::isAvailable()
{
	std::lock_guard<std::mutex> lock(mtx);
	return this->available;
}

void Fork::setAvailability(bool set)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->available = set;
}

bool Fork::takeIfAvailable()
{
	std::lock_guard<std::mutex> lock(mtx);
	if (this->available)
	{
		this->available = false;
		return true;
	}
	else 
	{
		return false;
	}
}
