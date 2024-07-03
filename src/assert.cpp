#include "assert.hpp"
#include "process.hpp"

namespace brb
{
	void ensure(bool condition, const char msg[])
	{
		if (condition)
			return;

		// Print the message if there is one
		if (msg)
		{
			// print
		}

		exit(1);
	}
}
