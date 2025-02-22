#include "print.hpp"
#include "string.hpp"

u8 brb_main(brb::vector<char*> args)
{
	brb::printv("argument count: ", args.size(), "\n");

	for (u64 i = 0; i < args.size(); ++i)
		brb::printv("argv[", i, "]: ", args[i], "\n");

	brb::string str1 = "Hello world\n";
	brb::string str2 = "Hello worls\n";

	if (str1 == str2)
		brb::print("strings match\n");
	else
		brb::print("strings don't match\n");

	return 0;
}
