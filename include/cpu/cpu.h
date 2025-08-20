#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

// CPU register
#define NUM_REGISTERS 32
#define ZERO_REGISTER 0

typedef struct {
  uint32_t regs[NUM_REGISTERS];  // General purpose registers
  uint32_t pc;                   // Program Counter
  uint32_t hi, lo;               // "high-order-bit" or remainder && "low-order-bit" or quotient
  bool running;                  // CPU state flag
  uint64_t cycle_count;          // Performance counter
} cpu_state_t;

cpu_state_t* cpu_create(void);
void cpu_destroy(cpu_state_t* cpu);
void cpu_reset(cpu_state_t * cpu);
void cpu_write_register(cpu_state_t* cpu, unsigned int reg_num, uint32_t value);
uint32_t cpu_read_register(cpu_state_t* cpu, unsigned int reg_num);

#endif // CPU_H
