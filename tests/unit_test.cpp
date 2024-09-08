#include "array.hpp"
#include "math.hpp"
#include "memory.hpp"
#include "print.hpp"
#include "scoped_ptr.hpp"
#include "string.hpp"
#include "testing.hpp"
#include "vector.hpp"

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
	{
		constexpr u64 data_size = 32;
		constexpr mu16 value = 3;

		mu16* data = new mu16[data_size];
		fill(data, data_size, value);

		bool all_values_match = true;
		for (mu64 i = 0; i < data_size; ++i)
		{
			if (data[i] != value)
			{
				all_values_match = false;
				break;
			}
		}
		test.check("fill()", all_values_match);

		delete[] data;
	}
	{
		constexpr u64 data_size = 16;
		mu16* data_a = new mu16[data_size];
		mu16* data_b = new mu16[data_size];

		fill<mu16>(data_a, data_size, 42);
		memcpy(data_a, data_b, data_size);
		test.check("memcpy() and memcmp() (matching)", memcmp(data_a, data_b, data_size));

		delete[] data_a;
		delete[] data_b;
	}
	{
		constexpr u64 data_size = 16;
		mu16* data_a = new mu16[data_size];
		mu16* data_b = new mu16[data_size];

		fill<mu16>(data_a, data_size, data_size);
		test.check("memcpy() and memcmp() (not matching)", !memcmp(data_a, data_b, data_size));

		delete[] data_a;
		delete[] data_b;
	}
}

void scoped_ptr_tests(testing& test)
{
	{
		scoped_ptr<mi32> ptr;
		*ptr.get() = 1234;
		test.check("default initialized scoped_ptr", *ptr.get() == 1234);
	}
	{
		scoped_ptr<mi32> ptr = make_scoped(64);
		test.check("scoped_ptr initialized with make_scoped()", *ptr.get() == 64);
	}
	{
		constexpr u8 data_size = 4;
		scoped_ptr<mi32> ptr = make_scoped<mi32, data_size>();
		fill(ptr.get(), data_size, 42);
		test.check("scoped_ptr array initialized with make_scoped()", ptr.get()[3] == 42);
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
	{
		string s('-', 4);
		test.check("string creation with set amount of repeating chars (str)", s == "----");
		test.check("string creation with set amount of repeating chars (size)", s.size() == 4);
	}
	{
		string s = "asd";
		s.push_back('f');
		test.check("string push_back()", s == "asdf");
		s.pop_back();
		test.check("string pop_back()", s == "asd");
	}
	{
		string s = "hello";
		s += "_world";
		test.check("string += char*", s == "hello_world");
	}
}

void math_tests(testing& test)
{
	test.check("square(2)", square(2) == 4);
	test.check("square(-2)", square(-2) == 4);
	test.check("pow(2, 0)", pow(2, 0) == 1);
	test.check("pow(2, 1)", pow(2, 1) == 2);
	test.check("pow(2, 2)", pow(2, 2) == 4);
	test.check("pow(2, 3)", pow(2, 3) == 8);
	test.check("pow(2, -2)", pow(2, -2) == 0.25);
	test.check("pow(0, 0)", pow(0, 0) == 1);
	test.check("pow(0, 1)", pow(0, 1) == 0);
	test.check("pow(0, 2)", pow(0, 2) == 0);
	test.check("floor(2.5)", floor(2.5) == 2);
	test.check("floor(2.9)", floor(2.9) == 2);
	test.check("floor(3.0)", floor(3.0) == 3);
	test.check("floor(-3.5)", floor(-3.5) == -3);
}

void vector_tests(testing& test)
{
	// the minimum capacity is 8 as of now
	// pls update this if it changes
	u64 min_vec_size = 8;

	{
		brb::vector<mi32> vec;
		test.check("vector empty()", vec.empty());

		vec.push_back(32);
		test.check("vector with one element (size)", vec.size() == 1);
		test.check("vector with one element (capacity)", vec.capacity() == min_vec_size);
		test.check("vector with one element (data)", vec[0] == 32);
		test.check("vector !empty()", !vec.empty());
	}
	{
		brb::vector<mi32> vec;
		constexpr u8 target_size = 64;

		for (mu8 i = 0; i < target_size; ++i)
			vec.push_back(i);

		test.check("vector with multiple elements (size)", vec.size() == target_size);
		test.check("vector with multiple elements (capacity)", vec.capacity() > vec.size());

		// compare the data to an equivalent array
		brb::array<mi32, target_size> arr;
		for (mu8 i = 0; i < target_size; ++i)
			arr[i] = i;

		test.check("vector with multiple elements (data)", memcmp(vec.data(), arr.data(), target_size));
	}
	{
		brb::vector<mi32> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.pop_back();

		test.check("vector pop_back() (size)", vec.size() == 2);
		test.check("vector pop_back() (capacity)", vec.capacity() > vec.size());
		test.check("vector pop_back() (data [0])", vec[0] == 1);
		test.check("vector pop_back() (data [1])", vec[1] == 2);
	}
	{
		brb::vector<mu64> vec;
		vec.resize(12);
		vec[10] = 2;

		test.check("vector resizing (size)", vec.size() == 12);
		test.check("vector resizing (capacity)", vec.capacity() == 12);
		test.check("vector resizing (data)", vec[10] == 2);
	}
	{
		constexpr u64 target_size = 64;
		brb::vector<brb::array<mu64, 64>> vec;
		test.check("vector push_back() with arrays (empty)", vec.empty());

		for (mu64 i = 0; i < target_size; ++i)
		{
			brb::array<mu64, 64> arr;
			vec.push_back(arr);
		}

		test.check("vector push_back() with arrays (size)", vec.size() == target_size);
		test.check("vector push_back() with arrays (capacity)", vec.capacity() > target_size);
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
	run_test(scoped_ptr_tests);
	run_test(string_tests);
	run_test(math_tests);
	run_test(vector_tests);

	test.check("unit tests don't leak memory", brb::allocated_block_count() == 0);
	return 0;
}
