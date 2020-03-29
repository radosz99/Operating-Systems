#pragma once
#include "Table.hpp"
//Start obiadu i powiadomienie wszystkich w¹tków filozofów
void Table::dinnerStart()
{
	std::cout << "XDDD" << std::endl;
	std::cout << "XDDD" << std::endl;
	setup.talk.letEveryoneKnow();
}

void Table::dinnerStop()
{
	setup.setIfFinished(true);
}