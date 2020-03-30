#pragma once
#include <atomic>
#include "Talk.hpp"

class TableSetup
{
private:
	std::atomic<bool> done { false };

public:
	Talk talk;
	bool getIfFinished();
	void setIfFinished(bool ifDone);


};
