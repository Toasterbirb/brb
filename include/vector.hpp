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
		constexpr void clear() { _size = 0; }

		void push_back(T data)
		{
			++_size;

			// resize the vector if the size goes over the capacity
			if (_size > _capacity) [[unlikely]]
			{
				// if the vector is empty, resize to the minimum size
				// otherwise multiply the capacity by the growth factor
				_capacity = _capacity == 0 ? minimum_size : _capacity * growth_factor;

				T* new_data = new T[_capacity * sizeof(T)];

				// there's no need to copy data or delete any old data if
				// the vector was empty before this point
				if (_size - 1 > 0)
				{
					memcpy(_data, new_data, _size);
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

		void resize(u64 element_count)
		{
			// allocate a new block of memory and only copy over
			// data up-to the element_count

			u64 elements_to_copy = _size < element_count ? _size : element_count;
			_size = element_count;
			_capacity = element_count;

			T* new_data = new T[element_count * sizeof(T)];

			memcpy(_data, new_data, elements_to_copy);
			delete[] _data;
			_data = new_data;
		}

		void reserve(u64 element_count)
		{
			// no need to reserve more memory if the capacity
			// is already higher than the requested new element count
			if (element_count <= _capacity)
				return;

			// update the capacity and allocate a new bigger block
			_capacity = element_count;
			T* new_data = new T[element_count * sizeof(T)];

			// copy the data over and delete the old block of memory
			memcpy(_data, new_data, _size);
			delete[] _data;
			_data = new_data;
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

		void operator=(const vector<T>& other)
		{
			if (other._size > _size)
				resize(other._size);

			memcpy(other._data, _data, other._size);
		}

		bool operator==(const vector<T>& other) const
		{
			if (_size != other._size)
				return false;

			return memcmp(_data, other._data, _size * sizeof(T));
		}

		bool operator!=(const vector<T>& other) const
		{
			if (_size != other._size)
				return true;

			return !memcmp(_data, other._data, _size * sizeof(T));
		}

		mf32 growth_factor{1.5};

	private:
		constexpr static u64 minimum_size{8};

		mu64 _size{0};
		mu64 _capacity{0};
		T* _data{nullptr};
	};
}
