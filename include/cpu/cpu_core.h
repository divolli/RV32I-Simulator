#ifndef CPU_CORE_H
#define CPU_CORE_H

#include "decode/instruction.h"

// Register file
typedef struct {
    uint32_t registers[NUM_REGISTERS];  // x0-x31, x0 is hardwired to 0
} register_file_t;

// Memory subsystem
typedef struct {
  uint8_t* data;
  size_t size;
  uint32_t base_address;
} memory_bank_t;

// Pipeline stage registers

// IF/ID Pipeline Register
typedef struct {
  uint32_t pc;                    // Program counter of fetched instruction
  uint32_t instruction;           // Raw 32-bit instruction
  bool valid;                     // Pipeline stage contains valid data
  bool stalled;                   // Pipeline stage is stalled
} if_id_register_t;

// ID/EX Pipeline Register
typedef struct {
  uint32_t pc;                    // PC of instruction
  instruction_t decoded_inst;     // Decoded instruction
  control_signals_t control;      // Control signals

  // Register file outputs
  uint32_t rs1_data;              // Contents of rs1
  uint32_t rs2_data;              // Contents of rs2

  // Immediate value
  int32_t immediate;              // Sign-extended immediate

  // Pipeline control
  bool valid;
  bool stalled;
} id_ex_register_t;

// EX/MEM Pipeline Register
typedef struct {
  uint32_t pc;                    // PC of instruction
  instruction_t decoded_inst;     // Decoded instruction
  control_signals_t control;      // Control signals

  // Execution results
  uint32_t alu_result;            // ALU computation result
  bool alu_zero;                  // ALU zero flag

  // Branch/Jump results
  uint32_t branch_target;         // Calculated branch target
  bool branch_taken;              // Branch condition result
  uint32_t jump_target;           // Calculated jump target

  // Memory operation data
  uint32_t memory_write_data;     // Data to write to memory (rs2)

  // Pipeline control
  bool valid;
} ex_mem_register_t;

// MEM/WB Pipeline Register
typedef struct {
  instruction_t decoded_inst;     // Decoded instruction
  control_signals_t control;      // Control signals

  // Results to write back
  uint32_t alu_result;            // ALU result
  uint32_t memory_data;           // Data loaded from memory
  uint32_t pc_plus_4;             // PC+4 for link register

  // Pipeline control
  bool valid;
} mem_wb_register_t;

// Complete CPU state
typedef struct {
  // Architectural state (visible to software)
  uint32_t pc;                    // Program counter
  register_file_t reg_file;       // Register file

  // Memory system
  memory_bank_t instruction_memory;
  memory_bank_t data_memory;

  // Pipeline registers
  if_id_register_t if_id;
  id_ex_register_t id_ex;
  ex_mem_register_t ex_mem;
  mem_wb_register_t mem_wb;

  // Pipeline control state
  bool pipeline_stalled;          // Pipeline is stalled due to hazard
  bool pipeline_flushed;          // Pipeline needs to be flushed
  uint32_t stall_cycles;          // Number of cycles pipeline has been stalled

  // Performance counters
  uint64_t total_cycles;          // Total clock cycles
  uint64_t total_instructions;    // Instructions completed (retired)
  uint64_t pipeline_stalls;       // Number of pipeline stalls
  uint64_t branch_instructions;   // Branch instructions executed
  uint64_t branch_mispredictions; // Mispredicted branches

  // Debug and trace state
  bool single_step_mode;          // Execute one instruction at a time
  bool trace_enabled;             // Enable instruction tracing
  uint32_t breakpoint_address;    // Debug breakpoint address
  bool breakpoint_enabled;        // Breakpoint is active
} cpu_state_t;

// CPU lifecycle functions
cpu_state_t* cpu_init(void);
void cpu_reset(cpu_state_t* cpu);
void cpu_destroy(cpu_state_t* cpu);

// Register file operations
uint32_t register_read(const cpu_state_t* cpu, uint8_t reg_num);
void register_write(cpu_state_t* cpu, uint8_t reg_num, uint32_t value);

// Memory operations
bool memory_init(memory_bank_t* memory, size_t size, uint32_t base_addr);
void memory_destroy(memory_bank_t* memory);

// Debug and inspection functions
void print_cpu_state(const cpu_state_t* cpu);
void print_register_file(const cpu_state_t* cpu);
void print_pipeline_state(const cpu_state_t* cpu);

#endif // CPU_CORE_H
