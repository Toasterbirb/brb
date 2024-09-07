#pragma once

#include "types.hpp"

namespace brb
{
	class testing
	{
	public:
		void check(const char* test_name, const bool expression);

	private:
		mu64 pass_count{0};
		mu64 fail_count{0};

		void pass();
		void fail();
	};
}
