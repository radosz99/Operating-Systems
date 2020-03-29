#include "Chopstick.hpp"

Chopstick::Chopstick(int const ChopstickId, int const ownerId) :
	id(ChopstickId), owner(ownerId), dirty(true)
{}

void Chopstick::request(int const ownerId)
{
	while (owner != ownerId)
	{
		if (dirty)
		{
			std::lock_guard<std::mutex> lock(mutex);

			dirty = false;
			owner = ownerId;
		}
		else
		{
			channel.wait();
		}
	}
}

void Chopstick::done_using()
{
	dirty = true;
	channel.notifyall();
}
