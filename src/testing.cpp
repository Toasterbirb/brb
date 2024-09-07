#include "print.hpp"
#include "testing.hpp"

namespace brb
{
	void testing::check(const char* test_name, const bool expression)
	{
		if (expression)
			pass();
		else
			fail();

		print(test_name);
		print("\n");
	}

	void testing::pass()
	{
		print("\033[0;32mPASS:\033[0m ");
		++pass_count;
	}

	void testing::fail()
	{
		print("\033[0;31mFAIL:\033[0m ");
		++fail_count;
	}
}
