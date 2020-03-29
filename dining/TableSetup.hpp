#pragma once
#include <atomic>
#include "Talk.hpp"

class table_setup
{
private:
	std::atomic<bool> done { false };

public:
	Talk talk;
	bool getIfFinished() const
	{
		return done;
	}

	void setIfFinished(bool ifDone)
	{
		done.exchange(ifDone);
	}


};