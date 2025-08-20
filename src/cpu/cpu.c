#include "cpu/cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cpu_state_t* cpu_create(void){
  // allocate memory for cpu struct
  cpu_state_t* cpu = (cpu_state_t*) calloc(1,sizeof(cpu_state_t)); // I used calloc to initialize variables in this struct

    // Check for allocation error
    if (!cpu) {
      fprintf(stderr, "Error: Failed to allocate memory for CPU\n");
      return NULL;
    }

  // Initialize CPU state
  cpu->running = false;
  cpu->pc = 0x00400000;  // Typical MIPS program start address

  // Success return pointer to cpu struct
  return cpu;
}


void cpu_destroy(cpu_state_t* cpu){
  if (!cpu) return; // There are null as cpu so we return
  free(cpu); // Free memory
}


void cpu_reset(cpu_state_t * cpu){
  if(!cpu) return;
  cpu->cycle_count = 0;
  cpu->running = false;
  cpu->hi = 0;
  cpu->lo = 0;
  cpu->pc = 0x00400000;
  memset(cpu->regs, 0, sizeof(cpu->regs));
}



void cpu_write_register(cpu_state_t* cpu, unsigned int reg_num, uint32_t value){
  // Validate inputs
  if (!cpu) {
    fprintf(stderr, "Error: NULL CPU pointer\n");
    return;
  }

  if (reg_num >= NUM_REGISTERS) {
    fprintf(stderr, "Error: Invalid register number %u\n", reg_num);
    return;
  }

  // Protect R0 - always stays zero
  if (reg_num == ZERO_REGISTER) {
    return;
  }

  // Write to register
  cpu->regs[reg_num] = value;
}


uint32_t cpu_read_register(cpu_state_t* cpu, unsigned int reg_num){
  // Validate inputs
  if (!cpu) {
    fprintf(stderr, "Error: NULL CPU pointer\n");
    return 0;
  }

  if (reg_num >= NUM_REGISTERS) {
    fprintf(stderr, "Error: Invalid register number %u\n", reg_num);
    return 0;
  }

  // R0 always returns 0
  if (reg_num == ZERO_REGISTER) {
    return 0;
  }

  return cpu->regs[reg_num];
}
