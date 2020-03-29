#include <array>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <condition_variable>
#include "Logic.hpp"

void dine()
{
	std::cout << "Dinner started!" << std::endl;

	{
		Table table;
		table.start();
		std::this_thread::sleep_for(std::chrono::seconds(60));
		table.stop();
	}

	std::cout << "Dinner done!" << std::endl;
}


int main()
{
	dine();

	return 0;
}