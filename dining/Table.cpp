#include "Table.hpp"

//Start obiadu i powiadomienie wszystkich w�tk�w filozof�w
void Table::dinnerStart()
{
	std::cout << "Dinner starting" << std::endl;
	setup.talk.letEveryoneKnow();
}

void Table::dinnerStop()
{
	setup.setIfFinished(true);
}
