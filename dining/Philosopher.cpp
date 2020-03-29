#include <array>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <condition_variable>
#include "Random.hpp"
#include "Philosopher.hpp"
#include <sstream>


Philosopher::Philosopher(int id, std::string n, table_setup & s, Chopstick & l, Chopstick & r) :
	id(id), name(n), setup(s), leftChopstick(l), rightChopstick(r), thread(&Philosopher::run, this)
{
}

Philosopher::~Philosopher()
{
	thread.join();
}

void Philosopher::run()
{
	setup.talk.wait();
	while(!setup.getIfFinished())
	{
		think();
		eat();
	} 
}

void Philosopher::think()
{
	print(" is thinking ");
	wait();
	state = State::HUNGRY;
}

void Philosopher::eat()
{
	leftChopstick.ask(id);
	rightChopstick.ask(id);
	std::scoped_lock lock(rightChopstick.getMutex(), leftChopstick.getMutex());

	state = State::EATING;
	print(" started eating.");
	wait();
	print(" finished eating.");
	state = State::THINKING;
	leftChopstick.mealFinished();
	rightChopstick.mealFinished();

}

void Philosopher::wait()
{
	int delayCount = Random().randomInt(60, 200);

	for (int i = 1; i <= delayCount; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		progress = static_cast<float>(i) / static_cast<float>(delayCount);
		nothungry = nothungry + 50;
	}
	progress = 0.0f;
}

void Philosopher::print(std::string text)
{
	std::ostringstream s1;
	s1 << name << text << std::endl;
	std::string s2 = s1.str();
	std::cout << s2;
}

State Philosopher::getState()
{
	return state;
}

float Philosopher::getProgress()
{
	return progress;
}

std::string Philosopher::getName()
{
	return name;
}

std::string Philosopher::getStateString() 
{
	switch (state)
	{
	case State::HUNGRY:
		return "HUNGRY";
	case State::EATING:
		return "EATING";
	case State::THINKING:
		return "THINKING";
	}

return "NONE";
}

