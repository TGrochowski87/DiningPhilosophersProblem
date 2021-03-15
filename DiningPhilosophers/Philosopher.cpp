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

Fork* Philosopher::getRightFork()
{
	return this->right;
}

void Philosopher::setLeftFork(Fork* fork)
{
	this->left = fork;
}

Fork* Philosopher::getLeftFork()
{
	return this->left;
}

void Philosopher::takeLeft()
{
	this->hasLeft = true;
	this->left->setAvailability(false);
}

void Philosopher::takeRight()
{
	this->hasRight = true;
	this->right->setAvailability(false);
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
			if (this->left->isAvailable() && !this->hasLeft)
			{
				std::cout << this->id << " has taken fork " << this->left->getPriority() << std::endl;
				takeLeft();
				this->status = "Philosopher " + std::to_string(this->id) + " has taken fork " + std::to_string(this->left->getPriority());
				//continue;
			}
			else if(!this->left->isAvailable() && this->hasLeft)
			{
				if (this->right->isAvailable() && !this->hasRight)
				{
					takeRight();
					this->status = "Philosopher " + std::to_string(this->id) + " has taken fork " + std::to_string(this->right->getPriority());
					//continue;
				}
				else if (!this->right->isAvailable() && this->hasRight)
				{
					this->status = "Philosopher " + std::to_string(this->id) + " is eating";
					eat();
				}
				else
				{
					this->status = "Philosopher " + std::to_string(this->id) + " is waiting";
					this->timeWaiting += 0.1;
					//continue;
				}
			}
			else 
			{
				this->status = "Philosopher " + std::to_string(this->id) + " is waiting";
				this->timeWaiting += 0.1;
				//continue;
			}
		}
		else
		{
			if (this->right->isAvailable() && !this->hasRight)
			{
				std::cout << this->id << " has taken fork " << this->right->getPriority() << std::endl;
				takeRight();
				this->status = "Philosopher " + std::to_string(this->id) + " has taken fork " + std::to_string(this->right->getPriority());
				//continue;
			}
			else if (!this->right->isAvailable() && this->hasRight)
			{
				if (this->left->isAvailable() && !this->hasLeft)
				{
					takeLeft();
					this->status = "Philosopher " + std::to_string(this->id) + " has taken fork " + std::to_string(this->left->getPriority());
					//continue;
				}
				else if (!this->left->isAvailable() && this->hasLeft)
				{
					this->status = "Philosopher " + std::to_string(this->id) + " is eating";
					eat();
				}
				else
				{
					this->status = "Philosopher " + std::to_string(this->id) + " is waiting";
					this->timeWaiting += 0.1;
					//continue;
				}
			}
			else
			{
				this->status = "Philosopher " + std::to_string(this->id) + " is waiting";
				this->timeWaiting += 0.1;
				//continue;
			}
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
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