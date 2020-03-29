#pragma once
#include <string>
#include <array>
#include <thread>
#include "Table.hpp"

class UI
{
public:
	UI(const std::array<Philosopher, 7>& philosophers, Table& table);
	~UI();

	bool isReady() const;

private:
	static constexpr int barHeight = 3;
	static constexpr int barWidth = 20;

	bool ready = false;

	std::unique_ptr<std::thread> viewThread;
	std::unique_ptr<std::thread> keyboardThread;



	Table& table;
	const std::array<Philosopher, 7>& philosophers;


};
