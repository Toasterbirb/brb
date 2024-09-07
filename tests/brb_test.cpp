#include "print.hpp"
#include "string.hpp"

mu8 brb_main()
{
	brb::string str1 = "Hello world\n";
	brb::string str2 = "Hello worls\n";

	if (str1 == str2)
		brb::print("strings match\n");
	else
		brb::print("strings don't match\n");

	return 0;
}
