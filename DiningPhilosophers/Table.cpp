#include "Table.h"

void Table::initializeTable(int amount, int eatingTime, int thinkingTime)
{
	for (int i = 0; i < amount; i++)
	{
		this->philosophers.push_back(new Philosopher(eatingTime, thinkingTime, i));
		this->forks.push_back(new Fork(i));
	}

	for (int i = 0; i < amount; i++)
	{
		this->philosophers[i]->setLeftFork(this->forks[i]);
		this->philosophers[i]->setRightFork(this->forks[(amount - 1 + i) % amount]);
	}
}

void Table::runSimulation()
{
	for (Philosopher* p : this->philosophers)
	{
		p->start();
	}

	bool isEveryoneReady = false;
	while (!isEveryoneReady)
	{
		for (Philosopher* p : this->philosophers)
		{
			if (!p->getStatus().empty())
			{
				isEveryoneReady = true;
			}
			else 
			{
				isEveryoneReady = false;
				break;
			}
		}
	}

	showStatusThread = std::make_unique<std::thread>([this]() {
		while (this->dinerPersists)
		{
			for (Philosopher* p : this->philosophers)
			{
				std::cout << p->getStatus() << std::endl;
			}
			std::cout << "\n------------------------------------------" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		});
}

void Table::endSimulation()
{

	for (Philosopher* p : this->philosophers)
	{
		p->stop();
	}

	this->dinerPersists = false;
	showStatusThread->join();

	for (Philosopher* p : this->philosophers)
	{
		std::cout << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "Philosopher " << p->getId() << ":" << std::endl;
		std::cout << "Was waiting for " << p->getWaitingTime() << " seconds." << std::endl;
		std::cout << "Was eating " << p->getEatingCount() << " times." << std::endl;
		delete p;
	}

	for (Fork* f : this->forks)
	{
		delete f;
	}
}