#include "memory.hpp"
#include "print.hpp"

struct test
{
	test()
	{
		brb::print("constructed\n");
	}

	~test()
	{
		brb::print("destructed\n");
	}

	const char* c = "test\n";
};

mu8 brb_main()
{
	test* t = new test[3];
	delete[] t;

	brb::assert(allocated_block_count() == 0, "memory leakage");

	return 0;
}
