#pragma once
#include <mutex>
#include <condition_variable>

class Talk
{
	std::mutex mutex;
	std::condition_variable cv;

public:
	void wait();

	void notifyall();
};