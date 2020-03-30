#include "Talk.hpp"
void Talk::wait()
{
	std::unique_lock<std::mutex> lock(mutex);
	while (!go)
	{
		cv.wait(lock);
	}
	go = true;
}

void Talk::letEveryoneKnow()
{
    std::unique_lock<std::mutex> lock(mutex);
    go=true;
	cv.notify_all();
}
