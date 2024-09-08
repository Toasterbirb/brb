#pragma once

#include "types.hpp"

namespace brb
{
	mu64 allocated_block_count();
	void* malloc(u64 size);
	void free(void* addr);

	template <typename T>
	void fill(T* addr, u64 size, const T value)
	{
		for (mu64 i = 0; i < size; ++i)
			addr[i] = value;
	}

	template <typename T>
	void memcpy(const T* src, T* dst, u64 element_count)
	{
		for (mu64 i = 0; i < element_count; ++i)
			dst[i] = src[i];
	}

	template <typename T>
	bool memcmp(const T* a, const T* b, u64 size)
	{
		for (mu64 i = 0; i < size; ++i)
			if (a[i] != b[i])
				return false;

		return true;
	}
}

void* operator new(u64 size);
void* operator new[](u64 size);
void operator delete(void* addr) noexcept;
void operator delete(void* addr, u64 size) noexcept;
void operator delete[](void* addr) noexcept;
void operator delete[](void* addr, u64 size) noexcept;
