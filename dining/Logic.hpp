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
constexpr  int no_of_philosophers = 7;



struct table_setup
{
	std::atomic<bool> done{ false };
	Talk channel;
};


class Philosopher
{
private:
	int id;
	std::string const name;
	table_setup& setup;
	Chopstick& left_Chopstick;
	Chopstick& right_Chopstick;
	std::thread lifethread;
	std::atomic<float> progress = 0.0f;

public:
	Philosopher(int const id, std::string const & n, table_setup & s, Chopstick & l, Chopstick & r);

	~Philosopher();

	void dine();

	void print(std::string const & text);
	void eat();

	void wait();


	void think();

};


class Table
{
	table_setup setup;

	std::array<Chopstick, no_of_philosophers> Chopsticks
	{
	   {
			{ 1, 1 },
			{ 2, 2 },
			{ 3, 3 },
			{ 4, 4 },
			{ 5, 5 },
			{ 6, 6 },
			{ 7, 1 },
		 }
	};


	std::array<Philosopher, no_of_philosophers> philosophers
	{
	   {
			{ 1, "Aristotle", setup, Chopsticks[0], Chopsticks[1] },
			{ 2, "Platon",    setup, Chopsticks[1], Chopsticks[2] },
			{ 3, "Descartes", setup, Chopsticks[2], Chopsticks[3] },
			{ 4, "Kant",      setup, Chopsticks[3], Chopsticks[4] },
			{ 5, "Nietzsche", setup, Chopsticks[4], Chopsticks[5] },
			{ 6, "Hume",      setup, Chopsticks[5], Chopsticks[6] },
			{ 7, "Russell",   setup, Chopsticks[6], Chopsticks[0] },
		  }
	};

public:
	void start();
	void stop();


};