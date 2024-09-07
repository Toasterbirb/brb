#include "assert.hpp"
#include "print.hpp"

constexpr char assertion_failed_msg[] = "assertion failed: ";
constexpr u64 assertion_failed_msg_len = brb::strlen(assertion_failed_msg);

constexpr char assertion_failed_no_msg[] = "assertion failed\n";
constexpr u64 assertion_failed_no_msg_len = brb::strlen(assertion_failed_no_msg);

namespace brb
{
	template <u64 str_len>
	void assert(const bool condition, string<str_len>& msg)
	{
		if (condition)
			return;

		// print the message
		print(assertion_failed_msg, assertion_failed_msg_len);
		print(msg);
		print("\n", 1);

		exit(-1);
		return;
	}

	void assert(const bool condition, const char* msg)
	{
		if (condition)
			return;

		// print the message
		print(assertion_failed_msg, assertion_failed_msg_len);
		print(msg, strlen(msg));
		print("\n", 1);

		exit(-1);
		return;
	}
}
