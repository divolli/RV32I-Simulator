#include "memory/memory.h"

memory_t* memory_create(size_t size){

}


void memory_destroy(memory_t* memory){

}


uint8_t memory_read_byte(memory_t* memory, uint32_t address){

}


uint32_t memory_read_word(memory_t* memory, uint32_t address){

}


void memory_write_byte(memory_t* memory, uint32_t address, uint8_t value){

}


void memory_write_word(memory_t* memory, uint32_t address, uint32_t value){

}


bool memory_is_valid_address(memory_t* memory, uint32_t address){

}
