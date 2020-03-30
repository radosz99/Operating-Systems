#include "Table.hpp"

//Start obiadu i powiadomienie wszystkich w¹tków filozofów
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

	const std::array<Philosopher, 7> & Table::getPhilosophers() {
		return philosophers;
	}

	const table_setup &Table::getSetup() {
		return setup;
	}

bool Table::getIsDinner() const
{
    return isDinner;
}

