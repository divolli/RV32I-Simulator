#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Memory configuration
#define MEMORY_SIZE (1024 * 1024) // 1MB memory
#define WORD_SIZE 4               // 4 bytes per word

typedef struct {
  uint32_t base_address;  // Base address (usually 0)
  uint8_t* data;         // Raw memory array
  size_t size;          // Total memory size
} memory_t;

memory_t* memory_create(size_t size);
void memory_destroy(memory_t* memory);
uint8_t memory_read_byte(memory_t* memory, uint32_t address);
uint32_t memory_read_word(memory_t* memory, uint32_t address);
void memory_write_byte(memory_t* memory, uint32_t address, uint8_t value);
void memory_write_word(memory_t* memory, uint32_t address, uint32_t value);
bool memory_is_valid_address(memory_t* memory, uint32_t address);


#endif // MEMORY_H
