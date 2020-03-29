#include <array>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <condition_variable>
#include "Table.hpp"

void run()
{
	Table table;
	table.dinnerStart();
	std::this_thread::sleep_for(std::chrono::seconds(30));
	table.dinnerStop();
}


int main()
{
	run();

	return 0;
}