#include "assert.hpp"
#include "print.hpp"
#include "string.hpp"

constexpr char assertion_failed_msg[] = "assertion failed: ";
constexpr u64 assertion_failed_msg_len = brb::strlen(assertion_failed_msg);

constexpr char assertion_failed_no_msg[] = "assertion failed\n";
constexpr u64 assertion_failed_no_msg_len = brb::strlen(assertion_failed_no_msg);

namespace brb
{
#ifndef NDEBUG
	void assert(const bool condition, string& msg)
	{
		if (condition)
			return;

		// print the message
		print(assertion_failed_msg, assertion_failed_msg_len);
		print(msg);
		print("\n", 1);

		syscall::kill(0, 6); // abort
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

		syscall::kill(0, 6); // abort
		return;
	}
#else
	void assert(const bool condition, string& msg) {}
	void assert(const bool condition, const char* msg) {}
#endif
}
