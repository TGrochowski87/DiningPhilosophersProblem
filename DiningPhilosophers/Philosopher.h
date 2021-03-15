#pragma once
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <utility>
#include <stdlib.h>
#include <atomic>
#include <time.h>
#include "Fork.h"

class Philosopher
{
public:
	Philosopher(int, int, int);

	void start();
	void stop();

	void setRightFork(Fork*);

	void setLeftFork(Fork*);

	void releaseLeft();
	void releaseRight();

	int getId();

	void act();
	void eat();

	float getWaitingTime();
	int getEatingCount();
	std::string getStatus();

private:
	int id;
	Fork* left;
	Fork* right;
	bool hasLeft;
	bool hasRight;

	float timeWaiting = 0.0;
	int counterEating = 0;

	int eatingTime;
	int thinkingTime;

	std::atomic_bool isDining = true;

	std::string status;

	std::unique_ptr<std::thread> lifeThread;
};

