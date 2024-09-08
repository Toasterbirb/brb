#include "process.hpp"
#include "syscalls.hpp"

// Define the program entry point
extern "C" void _start();

// The "main" source file will define this as its main function
mu8 brb_main();

void _start()
{
	u8 ret = brb_main();
	brb::exit(ret);
}

namespace brb
{
	void abort()
	{
		syscall::kill(0, 6);
	}

	void exit(u8 exit_code)
	{
		syscall::exit(exit_code);
	}
}
