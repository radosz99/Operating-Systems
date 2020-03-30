#pragma once
#include <array>
#include "TableSetup.hpp"
#include "Chopstick.hpp"
#include "Philosopher.hpp"
class Table
{
private:
    bool isDinner;
	const static int philosophersAmount = 7;
	TableSetup setup;

	std::array<Chopstick, philosophersAmount> chopsticks
	{
	   {
			{ 1, 1 },
			{ 2, 2 },
			{ 3, 3 },
			{ 4, 4 },
			{ 5, 5 },
			{ 6, 6 },
			{ 7, 1 },
		 }
	};


	std::array<Philosopher, philosophersAmount> philosophers
	{
	   {
			{ 1, "Austin", setup, chopsticks[0], chopsticks[1] },
			{ 2, "Barnie", setup, chopsticks[1], chopsticks[2] },
			{ 3, "Cedric", setup, chopsticks[2], chopsticks[3] },
			{ 4, "Darren", setup, chopsticks[3], chopsticks[4] },
			{ 5, "Elijah", setup, chopsticks[4], chopsticks[5] },
			{ 6, "Freddy", setup, chopsticks[5], chopsticks[6] },
			{ 7, "George",   setup, chopsticks[6], chopsticks[0] },
		  }
	};

public:
	void dinnerStart();
	void dinnerStop();
	const std::array<Philosopher, 7> &getPhilosophers();
	const std::array<Chopstick, 7> &getChopsticks();
	const TableSetup &getSetup();
    bool getIsDinner() const;


};
