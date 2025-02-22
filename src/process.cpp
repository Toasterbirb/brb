#include "process.hpp"
#include "syscalls.hpp"
#include "vector.hpp"

// Define the program entry point
extern "C" void _start();
extern "C" void init(u64 argc, char* argv[]);

// The "main" source file will define this as its main function
u8 brb_main(const brb::vector<char*>& args);

void init(u64 argc, char* argv[])
{
	brb::vector<char*> args;
	for (u64 i = 0; i < argc; ++i)
		args.push_back(argv[i]);

	brb_main(args);
}

namespace brb
{
	void abort()
	{
		syscall::kill(0, 6);
	}
}
