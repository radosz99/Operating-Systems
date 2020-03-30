
#include <atomic>
#include "TableSetup.hpp"

	bool TableSetup::getIfFinished()
	{
		return done;
	}

	void TableSetup::setIfFinished(bool ifDone)
	{
		done.exchange(ifDone);
	}
