#pragma once

#include "assert.hpp"
#include "memory.hpp"
#include "types.hpp"

namespace brb
{
	template <typename T>
	class vector
	{
	public:
		// don't reserve any space for empty vectors
		vector() {}

		~vector() { delete[] _data; }


		constexpr mu64 size() const { return _size; }
		constexpr bool empty() const { return _size == 0; }
		constexpr mu64 capacity() const { return _capacity; }
		constexpr T* data() const { return _data; }

		void push_back(T data)
		{
			++_size;

			// resize the vector if the size goes over the capacity
			if (_size > _capacity)
			{
				// if the vector is empty, resize to the minimum size
				// otherwise multiply the capacity by the growth factor
				_capacity = _capacity == 0 ? minimum_size : _capacity * growth_factor;

				T* new_data = new T[_capacity * sizeof(T)];

				// there's no need to copy data or delete any old data if
				// the vector was empty before this point
				// a vector is considered to have been empty if its size is less than
				// the minimum size
				if (_size > minimum_size)
				{
					memcpy(_data, new_data, _size - 1);
					delete[] _data;
				}

				_data = new_data;
			}

			// save the data into the vector
			_data[_size - 1] = data;
		}

		void pop_back()
		{
			if (_size > 0)
				_size--;
		}

		T& operator[](u64 index)
		{
			assert(index < _size, "index out-of-bounds");
			return _data[index];
		}

		T operator[](u64 index) const
		{
			assert(index < _size, "index out-of-bounds");
			return _data[index];
		}

		mf32 growth_factor{1.5};

	private:
		constexpr static u64 minimum_size{8};

		mu64 _size{0};
		mu64 _capacity{0};
		T* _data{nullptr};
	};
}
