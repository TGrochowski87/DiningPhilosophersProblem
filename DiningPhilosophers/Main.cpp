#include "Table.h"
#include <conio.h>
#include <cstdio>

using namespace std;

void main()
{
	srand(time(NULL));

	Table table;

	cout << "Dining Philosophers Problem\n" << endl;

	cout << "How many philosophers will dine today?" << endl;
	int amount;
	cin >> amount;

	cout << "\nHow long will eating last?" << endl;
	int eatingTime;
	cin >> eatingTime;

	cout << "\nHow long will thinking last?" << endl;
	int thinkingTime;
	cin >> thinkingTime;

	cout << endl;
	table.initializeTable(amount, eatingTime, thinkingTime);
	table.runSimulation();

	bool simulationRunning = true;

	while (_getch() != 32)
	{
	}

	table.endSimulation();
}