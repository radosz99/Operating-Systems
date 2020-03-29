#pragma once
#include <atomic>
#include "Talk.hpp"

class table_setup
{
private:
	std::atomic<bool> done { false };

public:
	Talk talk;
	bool getIfFinished();
	void setIfFinished(bool ifDone);


};
