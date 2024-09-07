#include "string.hpp"
#include "testing.hpp"

using namespace brb;

void string_tests(testing& test)
{
	{
		string a = "hello";
		string b = "hello";
		test.check("compare equal strings", a == b);
	}
	{
		string a = "hello";
		string b = "hella";
		test.check("compare non-equal strings with one char difference", a != b);
	}
	{
		string a = "helloo";
		string b = "hello";
		test.check("compare non-equal strings where the other one has more chars", a != b);
	}
}

mu8 brb_main()
{
	testing test;
	string_tests(test);

	return 0;
}
