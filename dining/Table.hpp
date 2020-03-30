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
	table_setup setup;

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
			{ 1, " Franky", setup, chopsticks[0], chopsticks[1] },
			{ 2, "  Tommy", setup, chopsticks[1], chopsticks[2] },
			{ 3, "Turkish", setup, chopsticks[2], chopsticks[3] },
			{ 4, " Mickey", setup, chopsticks[3], chopsticks[4] },
			{ 5, "    Avi", setup, chopsticks[4], chopsticks[5] },
			{ 6, "  Boris", setup, chopsticks[5], chopsticks[6] },
			{ 7, "   Tony",   setup, chopsticks[6], chopsticks[0] },
		  }
	};

public:
	void dinnerStart();
	void dinnerStop();
	const std::array<Philosopher, 7> &getPhilosophers();
	const std::array<Chopstick, 7> &getChopsticks();
	const table_setup &getSetup();
    bool getIsDinner() const;


};
