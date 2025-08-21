#include "memory/memory.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


memory_t* memory_create(size_t size){
  if (size < 1){
    fprintf(stderr, "Memory size to small\n");
    return NULL;
  }

  // Creating memory
  memory_t* memory = (memory_t *) calloc(1, sizeof(memory_t));

  //Error check
  if(!memory){
    fprintf(stderr, "Memory allocation error\n");
    return NULL;
  }

  memory->data = (uint8_t *) calloc(size, sizeof(uint8_t));

  //Error check
  if(!memory->data){
    free(memory); // free previous allocated memory
    fprintf(stderr, "Memory allocation error\n");
    return NULL;
  }
  memory->base_address = 0;
  memory->size = size;
  return memory;
}


void memory_destroy(memory_t* memory){
  if (!memory) return;

  free(memory->data);
  free(memory);
}


bool memory_is_valid_address(memory_t* memory, uint32_t address){
  if (!memory) return false;
  return (memory->base_address <= address) && (address < (memory->base_address + memory->size));
}


uint8_t memory_read_byte(memory_t* memory, uint32_t address){
  //Adress validation
  if (!memory_is_valid_address(memory, address)) {
    fprintf(stderr, "Address is not valid\n");
    return 0;
  }

  uint32_t index = address - memory->base_address;

  return memory->data[index];
}


void memory_write_byte(memory_t* memory, uint32_t address, uint8_t value){
  //Adress validation
  if (!memory_is_valid_address(memory, address)) {
    fprintf(stderr, "Address is not valid\n");
    return;
  }
  uint32_t index = address - memory->base_address;

  memory->data[index] = value;
}


uint32_t memory_read_word(memory_t* memory, uint32_t address){
  //Adress validation
  if (!memory_is_valid_address(memory, address + 3)) {
    fprintf(stderr, "Word access would exceed memory bounds\n");
    return 0;
  }

  uint32_t word = 0;
  uint32_t index = address - memory->base_address;

  for(unsigned short i = 0; i < WORD_SIZE; ++i){
    uint8_t byte = memory->data[index + i]; // get the byte
    word |= byte << (i * 8); // assign shifted bytes to word
  }

  return word;
}


void memory_write_word(memory_t* memory, uint32_t address, uint32_t value){
  //Adress validation
  if (!memory_is_valid_address(memory, address + 3)) {
    fprintf(stderr, "Word access would exceed memory bounds\n");
    return;
  }

  uint32_t index = address - memory->base_address;

  for(unsigned short i = 0; i < WORD_SIZE; ++i){
    uint8_t byte_to_write = (value >> (i * 8)) & 0xFF;
    memory->data[index + i] = byte_to_write;
  }
}
