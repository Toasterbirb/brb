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
		constexpr array(const T data[N]) { this->data = data; }

		constexpr u64 size() const { return _size; }

		constexpr void fill(const T value)
		{
			for (mu64 i = 0; i < _size; ++i)
				data[i] = value;
		}

		constexpr T operator[](u64 index) const
		{
			ensure(index < _size);
			return data[index];
		}

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
