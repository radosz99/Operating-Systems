#include "Table.hpp"

//Start obiadu i powiadomienie wszystkich w�tk�w filozof�w
void Table::dinnerStart()
{
    isDinner=true;
	setup.talk.letEveryoneKnow();
}

void Table::dinnerStop()
{
	setup.setIfFinished(true);
    isDinner=false;
}


const std::array<Chopstick, 7> & Table::getChopsticks() {
	return chopsticks;
}


	const std::array<Philosopher, 7> & Table::getPhilosophers() {
		return philosophers;
	}

	const TableSetup &Table::getSetup() {
		return setup;
	}

bool Table::getIsDinner() const
{
    return isDinner;
}

