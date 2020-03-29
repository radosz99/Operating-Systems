
#include "Talk.hpp"
void Talk::wait()
{
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock);
}

void Talk::notifyall()
{
	std::unique_lock<std::mutex> lock(mutex);
	cv.notify_all();
}