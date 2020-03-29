#include "Talk.hpp"
#include <iostream>
void Talk::wait()
{
	std::unique_lock<std::mutex> lock(mutex);
    while(!go)
	    cv.wait(lock);
}

void Talk::letEveryoneKnow()
{
    std::unique_lock<std::mutex> lock(mutex);
    go=true;
	cv.notify_all();
}
