
#include <atomic>
#include "TableSetup.hpp"

	bool table_setup::getIfFinished()
	{
		return done;
	}

	void table_setup::setIfFinished(bool ifDone)
	{
		done.exchange(ifDone);
	}
