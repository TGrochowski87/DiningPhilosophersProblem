#pragma once
#include <mutex>

class Fork
{
public:
	Fork(int);

	int getPriority();
	bool isAvailable();
	void setAvailability(bool);

private:
	bool availability;
	int priority;

	std::mutex mtx;
};

