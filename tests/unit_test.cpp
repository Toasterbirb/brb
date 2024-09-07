#include "array.hpp"
#include "memory.hpp"
#include "string.hpp"
#include "testing.hpp"

using namespace brb;

void array_tests(testing& test)
{
	{
		brb::array<mu32, 4> arr;
		arr.fill(5);

		test.check("array size()", arr.size() == 4);

		bool array_is_filled{true};
		for (mu8 i = 0; i < 4; ++i)
		{
			if (arr[i] != 5)
			{
				array_is_filled = false;
				break;
			}
		}
		test.check("array fill()", array_is_filled);

		arr[2] = 4;
		test.check("array value assignment operator", arr[2] == 4);
	}
	{
		brb::array<mu32, 16> arr_a;
		brb::array<mu32, 16> arr_b;
		brb::array<mu32, 16> arr_c;

		arr_a.fill(5);
		arr_b.fill(5);
		arr_c.fill(5);

		arr_c[1] = 2;

		test.check("compare equal arrays", arr_a == arr_b);
		test.check("compare non-equal arrays", arr_a != arr_c);
	}
}

void memory_tests(testing& test)
{
	{
		mu32* value = new mu32;
		*value = 5;
		test.check("new operator with unsigned 32bit integer (is not null)", value != nullptr);
		test.check("new operator with unsigned 32bit integer (value assignment)", *value = 5);
		delete value;
	}
	{
		constexpr u8 arr_size = 4;
		mu32* value_array = new mu32[arr_size];
		test.check("new operator with unsigned 32bit integer array (is not null)", value_array != nullptr);

		for (mu8 i = 0; i < arr_size; ++i)
			value_array[i] = i;

		test.check("new operator with unsigned 32bit integer (value assignment [1])", value_array[1] == 1);
		test.check("new operator with unsigned 32bit integer (value assignment [3])", value_array[3] == 3);
		delete[] value_array;
	}
}

void string_tests(testing& test)
{
	{
		test.check("strlen()", strlen("") == 0);
		test.check("strlen(asdf)", brb::strlen("asdf") == 4);
	}
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
	{
		string s;
		test.check("check if an empty string is empty", s.empty());
	}
	{
		string s = "asdf";
		test.check("check if a non-empty string is not empty", !s.empty());
	}
	{
		string s = "hello";
		s[1] = 'a';
		test.check("string modification (str)", s == "hallo");
		test.check("string modification (size)", s.size() == 5);
	}
	{
		string s = "hello";
		s = "asdf";
		test.check("string reassignment (str)", s == "asdf");
		test.check("string reassignment (size)", s.size() == 4);
	}
	{
		string s = "hello";
		s = "hello_hello";
		test.check("string reassignment that causes a resize (str)", s == "hello_hello");
		test.check("string reassignment that causes a resize (size)", s.size() == 11);
	}
	{
		string s = "hello";
		test.check("access string chars via index", s[1] == 'e');
	}
	{
		string s = "hello";
		s.clear();
		test.check("string clearing (str)", s == "");
		test.check("string clearing (size)", s.size() == 0);
	}
}

mu8 brb_main()
{
	testing test;

	const auto run_test = [&test](void(*test_func)(testing& test))
	{
		test_func(test);
		test.check("memory has not been leaked yet", brb::allocated_block_count() == 0);
	};

	run_test(array_tests);
	run_test(memory_tests);
	run_test(string_tests);

	test.check("unit tests don't leak memory", brb::allocated_block_count() == 0);
	return 0;
}
