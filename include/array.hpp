#pragma once

#include "assert.hpp"
#include "memory.hpp"
#include "types.hpp"

namespace brb
{
	template <typename T, u64 N>
	class array
	{
	public:
		constexpr array() {}
		constexpr array(const T data[N]) { this->data = data; }

		constexpr mu64 size() const { return _size; }
		T* data() { return &_data[0]; }

		constexpr void fill(const T value)
		{
			for (mu64 i = 0; i < _size; ++i)
				_data[i] = value;
		}

		constexpr T operator[](u64 index) const
		{
			assert(index < _size, "index out-of-bounds");
			return _data[index];
		}

		constexpr T& operator[](u64 index)
		{
			assert(index < _size, "index out-of-bounds");
			return _data[index];
		}

		constexpr void operator=(const array& other)
		{
			assert(other._size == _size, "tried to assign an array with a non-matching size");
			memcpy(other._data, _data, other._size * sizeof(T));
		}

		constexpr bool operator==(const array& other) const
		{
			for (mu64 i = 0; i < _size; ++i)
				if (_data[i] != other._data[i])
					return false;

			return true;
		}

		constexpr bool operator!=(const array& other) const
		{
			for (mu64 i = 0; i < _size; ++i)
				if (_data[i] != other._data[i])
					return true;

			return false;
		}

	private:
		T _data[N];
		u64 _size = N;
	};
}
