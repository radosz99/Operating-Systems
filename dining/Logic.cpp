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
#include "Logic.hpp"
#include <sstream>


Philosopher::Philosopher(int const id, std::string const & n, table_setup & s, Chopstick & l, Chopstick & r) :
	id(id), name(n), setup(s), left_Chopstick(l), right_Chopstick(r), lifethread(&Philosopher::dine, this)
{
}

Philosopher::~Philosopher()
{
	lifethread.join();
}

void Philosopher::dine()
{
	setup.channel.wait();

	do
	{
		think();
		eat();
	} while (!setup.done);
}

void Philosopher::print(std::string const & text)
{

	std::ostringstream s1;
	s1 << name << text << std::endl;
	std::string s2 = s1.str();
	std::cout << s2;
}

void Philosopher::eat()
{
	left_Chopstick.request(id);
	right_Chopstick.request(id);

	std::scoped_lock lock(right_Chopstick.getmutex(), left_Chopstick.getmutex());

	print(" started eating.");
	wait();
	print(" finished eating.");

	left_Chopstick.done_using();
	right_Chopstick.done_using();
}

void Philosopher::wait()
{
	int delayCount = Random().randomInt(15, 50);

	for (int i = 1; i <= delayCount; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		progress = static_cast<float>(i) / static_cast<float>(delayCount);
	}
	progress = 0.0f;
}


void Philosopher::think()
{
	print(" is thinking ");
	wait();
}


void Table::start()
{
	setup.channel.notifyall();
}

void Table::stop()
{
	setup.done = true;
}

