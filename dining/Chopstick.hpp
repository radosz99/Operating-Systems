#pragma once
#include<mutex>
#include"Talk.hpp"
class Chopstick
{
	int id;
	int owner;
	bool dirty;
	std::mutex mutex;
	Talk channel;

public:
	Chopstick(int const ChopstickId, int const ownerId);

	void request(int const ownerId);

	void done_using();

	std::mutex& getmutex() { return mutex; }
};