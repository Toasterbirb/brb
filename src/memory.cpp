#include "assert.hpp"
#include "memory.hpp"
#include "print.hpp"
#include "syscalls.hpp"

// some constants from mman.h and mman-linux.h
constexpr u8 PROT_READ = 0x1;
constexpr u8 PROT_WRITE = 0x2;
constexpr u8 PROT_EXEC = 0x4;
constexpr u8 PROT_NONE = 0x0;
constexpr u8 MAP_SHARED = 0x01;
constexpr u8 MAP_PRIVATE = 0x02;
constexpr u8 MAP_SHARED_VALIDATE = 0x03;
constexpr u8 MAP_ANONYMOUS = 0x20;

// function definitions
void* allocate_new_block(const u64 size);

struct __attribute__((packed)) block
{
	block* next{nullptr};
	u64 size; // amount of usable memory pointed to by addr
	bool used{false};
	void* addr;

	void* mem_start_addr()
	{
		return this + sizeof(block*) + sizeof(u64) + sizeof(bool);
	}

	void* mem_end_addr()
	{
		return (char*)mem_start_addr() + size;
	}
};

constexpr u64 minimum_allocation{2048};
static_assert(sizeof(block) + sizeof(f128) < minimum_allocation);

static block blocks {nullptr, 0, false, nullptr};

// keep track of allocated blocks to spot memory leakage
static i64 block_allocation_counter{0};

void* allocate_new_block(const u64 size)
{
	// figure out the size of the new block
	// if the new block would be very small, allocate a bigger one so that we can
	// later on split this big block into smaller pieces without doing extra allocations
	const u64 block_size = size + sizeof(block);
	void* ptr = brb::syscall::mmap(0, block_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	brb::assert(ptr, "got a nullptr from mmap");

	// turn the ptr into a block
	block* new_block = reinterpret_cast<block*>(ptr);

	// setup the block values
	new_block->size = block_size - sizeof(block*) - sizeof(u64) - sizeof(bool);
	new_block->used = true;
	new_block->addr = new_block->mem_start_addr();

	// find the last block in the chain of memory blocks
	block* last_block = &blocks;
	while (last_block->next != nullptr)
		last_block = last_block->next;

	// add the new block to the chain
	last_block->next = new_block;

	return new_block->addr;
}

namespace brb
{
	i64 allocated_block_count()
	{
		return block_allocation_counter;
	}


	void* malloc(const u64 size)
	{
		block_allocation_counter++;

		// try to find a block would fit the information we are trying to allocate
		block* block_to_use = &blocks;
		while (block_to_use != nullptr)
		{
			if (!block_to_use->used && block_to_use->size >= size)
			{
				block_to_use->used = true;
				return block_to_use->addr;
			}

			block_to_use = block_to_use->next;
		}

		// we couldn't find a good block so just create a new one
		return allocate_new_block(size);
	}

	void free(void* addr)
	{
		assert(addr, "can't free a nullptr");
		assert(block_allocation_counter > 0, "more memory blocks have been freed than allocated");

		// calculate the location of the block
		block* b = (block*)((char*)addr - sizeof(bool) - sizeof(u64) - sizeof(block*));

		// mark the block as unused
		b->used = false;

		block_allocation_counter--;
	}
}

void* operator new(const u64 size)
{
	return brb::malloc(size);
}

void* operator new[](const u64 size)
{
	return brb::malloc(size);
}

void operator delete(void* addr) noexcept
{
	brb::free(addr);
}

void operator delete(void* addr, const u64 size) noexcept
{
	brb::free(addr);
}

void operator delete[](void* addr) noexcept
{
	brb::free(addr);
}

void operator delete[](void* addr, const u64 size) noexcept
{
	brb::free(addr);
}
