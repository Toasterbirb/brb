#include "Process.hpp"

// Define the program entry point
extern "C" void _start();

// The "main" source file will define this as its main function
int brb_main();

void _start()
{
	int ret = brb_main();
	brb::exit(ret);
}

namespace brb
{
	void exit(int exit_code)
	{
		asm(R"(
		.global exit
			exit:
				mov $1, %eax
				mov %edi, %ebx
				int $0x80
		)");
	}
}
