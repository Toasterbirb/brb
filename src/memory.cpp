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

block blocks {nullptr, nullptr, 0, true};

void* operator new(u64 size)
{
	// go through the memory blocks and attempt to find a fitting block

	block* b = &blocks;
	while ((b->used || b->size < size) && b->next != nullptr)
		b = b->next;

	// if no fitting blocks were found, allocate a new one and add it to the chain

	if (b->used)
	{
		u64 block_size = size + sizeof(block);
		block* new_block = static_cast<block*>(brb::syscall::mmap(0, block_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
		brb::assert(new_block != nullptr, "got a nullptr from mmap");

		// create a link between the last block and the new block
		b->next = new_block;

		// calculate the address where the data should go to
		new_block->addr = new_block + sizeof(block);

		// set the rest of the variables
		new_block->size = block_size;
		new_block->used = true;
		new_block->next = nullptr;

		// move into the new block
		b = new_block;
	}

	brb::assert(b->size != 0, "empty memory block");
	brb::assert(b->used, "new memory block left unused");
	brb::assert(b->addr != nullptr, "new address was a nullptr");
	return b->addr;
}
