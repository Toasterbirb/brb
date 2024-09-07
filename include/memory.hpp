#pragma once

#include "types.hpp"

namespace brb
{
	mu64 allocated_block_count();
	void* malloc(u64 size);
	void free(void* addr);
}

void* operator new(u64 size);
void* operator new[](u64 size);
void operator delete(void* addr) noexcept;
void operator delete(void* addr, u64 size) noexcept;
void operator delete[](void* addr) noexcept;
void operator delete[](void* addr, u64 size) noexcept;
