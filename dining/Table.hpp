#pragma once
#include <array>
#include "TableSetup.hpp"
#include "Chopstick.hpp"
#include "Philosopher.hpp"
class Table
{
private:
	const static int philosophersAmount = 5;
	table_setup setup;

	std::array<Chopstick, philosophersAmount> chopsticks
	{
	   {
			{ 1, 1 },
			{ 2, 2 },
			{ 3, 3 },
			{ 4, 4 },
			{ 5, 1 },
		 }
	};


	std::array<Philosopher, philosophersAmount> philosophers
	{
	   {
			{ 1, "Franky", setup, chopsticks[0], chopsticks[1] },
			{ 2, "Tommy",    setup, chopsticks[1], chopsticks[2] },
			{ 3, "Turkish", setup, chopsticks[2], chopsticks[3] },
			{ 4, "Mickey", setup, chopsticks[3], chopsticks[4] },
			{ 5, "Tony",   setup, chopsticks[4], chopsticks[0] },
		  }
	};

public:
	void dinnerStart();
	void dinnerStop();


};