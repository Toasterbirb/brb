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

struct block
{
	block* next;
	void* addr;
	mu64 size;
	bool used{false};

	static block* get_block_ptr(void* address)
	{
		return static_cast<block*>(address) - sizeof(block);
	}

};

constexpr u64 minimum_allocation{2048};
static_assert(sizeof(block) + sizeof(f128) < minimum_allocation);

static block blocks {nullptr, nullptr, 0, true};

// keep track of allocated blocks to spot memory leakage
static mu64 block_allocation_counter{0};

namespace brb
{
	block* new_block(u64 size);
	void split_block(block* b, u64 size);

	mu64 allocated_block_count()
	{
		return block_allocation_counter;
	}

	block* new_block(u64 size)
	{
		u64 new_block_size = size < minimum_allocation ? minimum_allocation + sizeof(block) : size + sizeof(block);
		block* new_block = static_cast<block*>(brb::syscall::mmap(0, new_block_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
		brb::assert(new_block != nullptr, "got a nullptr from mmap");

		assert(new_block_size > sizeof(block));
		new_block->size = new_block_size - sizeof(block);
		new_block->next = nullptr;
		new_block->addr = new_block + sizeof(block) + 1;

		return new_block;
	}

	/**
	 * @brief Split a block into two blocks
	 *
	 * @param b A pointer to the block to split
	 * @param size Amount of space to leave for the original block
	 */
	void split_block(block* b, u64 size)
	{
		assert(size != 0, "splitting a block into an empty one is not allowed");

		u64 block_offset = size + sizeof(block) + 1;

		block* new_block = reinterpret_cast<block*>(reinterpret_cast<mu64*>(b) + block_offset);
		assert(new_block + sizeof(block) + 1 < b + b->size + 1, "new block is out-of-bounds");

		new_block->used = false;
		new_block->addr = new_block + sizeof(block) + 1;
		new_block->next = nullptr;

		assert(b->size > block_offset);
		new_block->size = b->size - block_offset;
		assert(new_block->size > 0, "the new split block is empty");

		b->size = size;
		b->next = new_block;
	}

	void* malloc(u64 size)
	{
		if (size == 0)
			return nullptr;

		// go through the memory blocks and attempt to find a fitting block

		block* b = &blocks;
		while ((b->used || b->size < size) && b->next != nullptr)
			b = b->next;

		// if no fitting blocks were found, allocate new blocks and add them to the chain

		if (b->used)
		{
			print("new block allocated\n");
			block* new_b = new_block(size);
			b->next = new_b;
			b = new_b;
		}

		// split the block if possible
		if (b->size + sizeof(block) > (size + sizeof(block) + 1) * 4)
			split_block(b, size);

		b->used = true;

		brb::assert(b->size != 0, "empty memory block");
		brb::assert(b->used, "new memory block left unused");
		brb::assert(b->addr != nullptr, "new address was a nullptr");

		++block_allocation_counter;
		return b->addr;
	}

	void free(void* addr)
	{
		block* b = block::get_block_ptr(addr);
		b->used = false;
		--block_allocation_counter;
	}
}

void* operator new(u64 size)
{
	return brb::malloc(size);
}

void* operator new[](u64 size)
{
	return brb::malloc(size);
}

void operator delete(void* addr) noexcept
{
	brb::free(addr);
}

void operator delete(void* addr, u64 size) noexcept
{
	brb::free(addr);
}

void operator delete[](void* addr) noexcept
{
	brb::free(addr);
}

void operator delete[](void* addr, u64 size) noexcept
{
	brb::free(addr);
}
