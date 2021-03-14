#pragma once
#include <vector>
#include <algorithm>
#include "Philosopher.h"

class Table
{
public:
	void initializeTable(int, int, int);
	void runSimulation();
	void endSimulation();

private:
	std::atomic_bool dinerPersists = true;
	std::unique_ptr<std::thread> showStatusThread;

	std::vector<Philosopher*> philosophers;
	std::vector<Fork*> forks;
};

