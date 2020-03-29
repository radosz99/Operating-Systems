#include "Talk.hpp"
void Talk::wait()
{
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock);
}

void Talk::letEveryoneKnow()
{
	cv.notify_all();
}