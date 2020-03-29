#include "Chopstick.hpp"

Chopstick::Chopstick(int ChopstickId, int ownerId) :
	id(ChopstickId), owner(ownerId), dirty(true)
{}

void Chopstick::ask(int ownerId)
{
	while (owner != ownerId)
	{
		if (dirty)
		{
			std::scoped_lock<std::mutex> lock(mutex);
			dirty = false;
			owner = ownerId;
		}
		else
		{
			talk.wait();
		}
	}
}

void Chopstick::mealFinished()
{
	dirty = true;
	talk.letEveryoneKnow();
}
