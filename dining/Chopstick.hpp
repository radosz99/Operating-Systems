#pragma once
#include<mutex>
#include <atomic>
#include"Talk.hpp"
class Chopstick
{
private:
	int id;
	int owner;
	std::atomic<bool> dirty{ false };
	std::mutex mutex;
	Talk talk;

public:
	Chopstick(int ChopstickId, int ownerId);
	void ask(int ownerId);
	void mealFinished();

	std::mutex& getMutex() 
	{ 
		return mutex; 
	}

	int getId() {
		return id;
	}

    int getOwner() const;
};
