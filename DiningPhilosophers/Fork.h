#pragma once
#include <mutex>

class Fork
{
public:
	Fork(int);

	int getPriority();
	void setAvailability(bool);
	bool takeIfAvailable();

private:
	bool available = true;
	int priority;

	std::mutex mtx;
};

