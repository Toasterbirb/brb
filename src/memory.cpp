#include "assert.hpp"
#include "memory.hpp"
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
};

constexpr u64 minimum_allocation{1024};
static_assert(sizeof(block) + sizeof(f128) < minimum_allocation);

static block blocks {nullptr, nullptr, 0, true};

// keep track of allocated blocks to spot memory leakage
static mu64 block_allocation_counter{0};

namespace brb
{
	void split_block(block* b, u64 needed_size);

	mu64 allocated_block_count()
	{
		return block_allocation_counter;
	}

	void split_block(block* b, u64 needed_size)
	{
		block* next_block = static_cast<block*>(b->addr) + needed_size + 1;
		b->next = next_block;
		b->size = sizeof(block) + needed_size;

		next_block->addr = next_block + sizeof(block);
		next_block->next = nullptr;
		next_block->size = b->size - needed_size - 1;
		next_block->used = false;
	}

	void* malloc(u64 size)
	{
		// go through the memory blocks and attempt to find a fitting block

		block* b = &blocks;
		while ((b->used || b->size < size) && b->next != nullptr)
			b = b->next;

		// if no fitting blocks were found, allocate new blocks and add them to the chain

		if (b->used)
		{
			u64 needed_block_size = size + sizeof(block);
			u64 new_block_size = size < minimum_allocation ? minimum_allocation : size + sizeof(block);
			block* new_block = static_cast<block*>(brb::syscall::mmap(0, new_block_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
			brb::assert(new_block != nullptr, "got a nullptr from mmap");

			// create a link between the last block and the new block
			b->next = new_block;

			// calculate the address where the data should go to
			new_block->addr = new_block + sizeof(block);

			// set the rest of the variables
			new_block->size = new_block_size;
			new_block->used = true;
			new_block->next = nullptr;

			// move into the new block
			b = new_block;

			// create a new unused block after this current one if there's more space left that's unused
			if (needed_block_size < new_block_size)
				split_block(new_block, needed_block_size);
		}

		// split the block if possible
		if (b->size > size + sizeof(block))
			split_block(b, size + sizeof(block));

		// mark the block as used
		b->used = true;

		brb::assert(b->size != 0, "empty memory block");
		brb::assert(b->used, "new memory block left unused");
		brb::assert(b->addr != nullptr, "new address was a nullptr");

		++block_allocation_counter;
		return b->addr;
	}

	void free(void* addr)
	{
		block* b = static_cast<block*>(addr);
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
