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
#include "UI.hpp"
void run()
{
	Table table;
	UI ui(table.getPhilosophers(), table, table.getChopsticks());
	table.dinnerStart();
	while(table.getIsDinner());
}


int main()
{
	run();

	return 0;
}
