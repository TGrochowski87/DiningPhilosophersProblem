#include "Philosopher.h"

Philosopher::Philosopher(int eatingTime, int thinkingTime, int id)
{
	this->eatingTime = eatingTime + (rand() % 41 - 20) * eatingTime / 100;
	this->thinkingTime = thinkingTime + (rand() % 41 - 20) * thinkingTime / 100;

	this->id = id;
}

void Philosopher::start()
{
	lifeThread = std::make_unique<std::thread>([this]() {act(); });
}

void Philosopher::stop()
{
	this->isDining = false;
	this->lifeThread->join();
}

void Philosopher::setRightFork(Fork* fork)
{
	this->right = fork;
}

void Philosopher::setLeftFork(Fork* fork)
{
	this->left = fork;
}

void Philosopher::releaseLeft()
{
	this->hasLeft = false;
	this->left->setAvailability(true);
}

void Philosopher::releaseRight()
{
	this->hasRight = false;
	this->right->setAvailability(true);
}

int Philosopher::getId()
{
	return this->id;
}

void Philosopher::act()
{
	while (this->isDining.load())
	{

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		if (this->left->getPriority() < this->right->getPriority())
		{
			if (!this->hasLeft)
			{
				if (this->left->takeIfAvailable())
				{
					this->hasLeft = true;
					this->status = "Philosopher " + std::to_string(this->id) + " has taken fork " + std::to_string(this->left->getPriority());
				}
				else
				{
					this->status = "Philosopher " + std::to_string(this->id) + " is waiting";
					this->timeWaiting += 0.1;
				}
			}
			else if (!this->hasRight)
			{
				if (this->right->takeIfAvailable())
				{
					this->hasRight = true;
					this->status = "Philosopher " + std::to_string(this->id) + " has taken fork " + std::to_string(this->right->getPriority());
				}
				else
				{
					this->status = "Philosopher " + std::to_string(this->id) + " is waiting";
					this->timeWaiting += 0.1;
				}
			}
			else
			{
				this->status = "Philosopher " + std::to_string(this->id) + " is eating";
				eat();
			}
		}
		else
		{
			if (!this->hasRight)
			{
				if (this->right->takeIfAvailable())
				{
					this->hasRight = true;
					this->status = "Philosopher " + std::to_string(this->id) + " has taken fork " + std::to_string(this->right->getPriority());
				}
				else
				{
					this->status = "Philosopher " + std::to_string(this->id) + " is waiting";
					this->timeWaiting += 0.1;
				}
			}
			else if (!this->hasLeft)
			{
				if (this->left->takeIfAvailable())
				{
					this->hasLeft = true;
					this->status = "Philosopher " + std::to_string(this->id) + " has taken fork " + std::to_string(this->left->getPriority());
				}
				else
				{
					this->status = "Philosopher " + std::to_string(this->id) + " is waiting";
					this->timeWaiting += 0.1;
				}
			}
			else
			{
				this->status = "Philosopher " + std::to_string(this->id) + " is eating";
				eat();
			}
		}
	}
}

void Philosopher::eat()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(this->eatingTime));
	this->counterEating++;
	releaseLeft();
	releaseRight();

	this->status = "Philosopher " + std::to_string(this->id) + " is thinking";
	std::this_thread::sleep_for(std::chrono::milliseconds(this->thinkingTime));
}

float Philosopher::getWaitingTime()
{
	return this->timeWaiting;
}


int Philosopher::getEatingCount()
{
	return this->counterEating;
}

std::string Philosopher::getStatus()
{
	return this->status;
}