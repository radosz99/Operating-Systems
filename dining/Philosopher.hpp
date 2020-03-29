#pragma once
#include <array>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <condition_variable>
#include "Talk.hpp"
#include "Chopstick.hpp"
#include "TableSetup.hpp"
#include "State.hpp"

class Philosopher
{
private:
	int hungry = 0;
	int nothungry = 0;
	int id;
	std::string name;
	table_setup& setup;
	Chopstick& leftChopstick;
	Chopstick& rightChopstick;
	std::thread thread;
	std::atomic<float> progress = 0.0f;
	std::atomic<State> state = State::THINKING;

public:
	Philosopher(int id, std::string n, table_setup & s, Chopstick & l, Chopstick & r);
	~Philosopher();

	void run();
	void print(std::string text);
	void eat();
	void wait();
	float getProgress() const;
    State getState() const;
    std::string getName() const;
    std::string getStateString() const;


	void think();

};

