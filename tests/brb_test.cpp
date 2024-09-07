#include "memory.hpp"
#include "print.hpp"
#include "string.hpp"

mu8 brb_main()
{
	char* character = new char;
	char* another_char = new char;

	*character = 'A';
	*another_char = 'B';

	char text[4];
	text[0] = *character;
	text[1] = *another_char;
	text[2] = '\n';
	text[3] = '\0';

	brb::print(text);

	return 0;
}
