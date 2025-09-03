#ifndef MEMORY_H
#define MEMORY_H

#include "cpu/cpu_core.h"

// Memory access functions with proper alignment and size handling
uint32_t memory_load_word(const memory_bank_t* memory, uint32_t address);
uint16_t memory_load_halfword(const memory_bank_t* memory, uint32_t address);
uint8_t memory_load_byte(const memory_bank_t* memory, uint32_t address);

void memory_store_word(memory_bank_t* memory, uint32_t address, uint32_t data);
void memory_store_halfword(memory_bank_t* memory, uint32_t address, uint16_t data);
void memory_store_byte(memory_bank_t* memory, uint32_t address, uint8_t data);

// Generic memory access with size and sign extension
uint32_t memory_load(const memory_bank_t* memory, uint32_t address, memory_size_t size, bool unsigned_load);
void memory_store(memory_bank_t* memory, uint32_t address, uint32_t data, memory_size_t size);

// Memory management
void memory_clear(memory_bank_t* memory);
bool memory_address_valid(const memory_bank_t* memory, uint32_t address, memory_size_t access_size);

// Program loading
bool load_program_from_file(memory_bank_t* memory, const char* filename);
bool load_program_from_array(memory_bank_t* memory, const uint32_t* program, size_t instruction_count);

// Memory inspection
void memory_dump(const memory_bank_t* memory, uint32_t start_addr, uint32_t length);
void memory_dump_instructions(const memory_bank_t* memory, uint32_t start_addr, uint32_t instruction_count);

#endif // MEMORY_H
