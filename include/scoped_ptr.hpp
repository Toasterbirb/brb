#pragma once

#include "types.hpp"

namespace brb
{
	template <typename T>
	class scoped_ptr
	{
	public:
		scoped_ptr() : _is_array(false) { ptr = new T; }
		scoped_ptr(T* ptr, const bool is_array = false) : ptr(ptr), _is_array(is_array) {}

		~scoped_ptr()
		{
			if (!_is_array)
				delete ptr;
			else
				delete[] ptr;
		}

		T* get() const { return ptr; }
		constexpr bool is_array() const { return _is_array; }

	private:
		T* ptr{nullptr};
		bool _is_array{false};
	};

	template <typename T>
	scoped_ptr<T> make_scoped(const T data)
	{
		T* ptr = new T(data);
		return scoped_ptr<T>(ptr, false);
	}

	template <typename T, u64 size>
	scoped_ptr<T> make_scoped()
	{
		static_assert(size > 0, "allocating less than a singular element is not allowed");
		T* ptr = new T[size];
		return scoped_ptr<T>(ptr, true);
	}
}
