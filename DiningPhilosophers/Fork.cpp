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
	return this->availability;
}

void Fork::setAvailability(bool set)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->availability = set;
}
