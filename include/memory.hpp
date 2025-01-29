#pragma once

#include "types.hpp"

namespace brb
{
	i64 allocated_block_count();
	void* malloc(const u64 size);
	void free(void* addr);

	template <typename T>
	void fill(T* addr, u64 element_count, const T value)
	{
		for (u64 i = 0; i < element_count; ++i)
			addr[i] = value;
	}

	template <typename T>
	void memcpy(const T* src, T* dst, const u64 element_count)
	{
		for (u64 i = 0; i < element_count; ++i)
			dst[i] = src[i];
	}

	template <typename T>
	bool memcmp(const T* a, const T* b, const u64 size)
	{
		for (u64 i = 0; i < size; ++i)
			if (a[i] != b[i])
				return false;

		return true;
	}
}

void* operator new(const u64 size);
void* operator new[](const u64 size);
void operator delete(void* addr) noexcept;
void operator delete(void* addr, const u64 size) noexcept;
void operator delete[](void* addr) noexcept;
void operator delete[](void* addr, const u64 size) noexcept;
