#include "print.hpp"
#include "read.hpp"
#include "string.hpp"

mu8 brb_main()
{
	brb::string<16> str;

	brb::print("Write something: ");
	brb::read(str);

	brb::print("Read string: ");
	brb::print(str);

	return 3;
}
