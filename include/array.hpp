#pragma once

#include "assert.hpp"
#include "types.hpp"

namespace brb
{
	template <typename T, u64 N>
	class array
	{
	public:
		constexpr array() {}
		constexpr array(T data[N])
		{
			this->data = data;
		}

		u64 size() const { return _size; }

		constexpr T& operator[](u64 index)
		{
			ensure(index < _size);
			return data[index];
		}

	private:
		T data[N];
		u64 _size = N;
	};
}
