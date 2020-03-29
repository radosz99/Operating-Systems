#include "UI.hpp"
#include <iostream>

UI::UI(const std::array<Philosopher, 7>& philosophers, Table& table) : philosophers(philosophers), table(table)
{
	std::cout << philosophers.size() << std::endl;
}

UI::~UI()
{
}

