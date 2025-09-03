#ifndef TRACE_H
#define TRACE_H

#include "cpu/cpu_core.h"
#include <stdio.h>

// Single trace entry
typedef struct {
  uint64_t cycle_number;          // Clock cycle when instruction completed
  uint32_t pc;                    // PC of instruction
  uint32_t instruction;           // Raw instruction word
  instruction_t decoded;          // Decoded instruction

  // Register state before execution
  uint32_t register_state[NUM_REGISTERS];

  // Memory access information (if any)
  bool memory_access;
  uint32_t memory_address;
  uint32_t memory_data;
  bool memory_write;              // true=write, false=read

  // Execution results
  uint32_t result_data;           // Data written to rd (if any)
  uint8_t result_register;        // Register written (rd)

  // Pipeline information
  uint32_t pipeline_stalls;       // Stalls caused by this instruction
  bool branch_taken;              // Was branch taken (for branches)
  uint32_t next_pc;               // Next PC after this instruction
} trace_entry_t;

// Execution tracer
typedef struct {
  trace_entry_t* entries;         // Circular buffer of trace entries
  size_t capacity;                // Maximum number of entries
  size_t count;                   // Current number of entries
  size_t write_index;             // Next write position

  FILE* trace_file;               // Optional file for trace output
  bool trace_to_file;             // Write trace to file
  bool trace_to_console;          // Print trace to console

  // Trace filtering
  bool trace_all_instructions;    // Trace every instruction
  bool trace_branches_only;       // Only trace branch instructions
  bool trace_memory_only;         // Only trace memory instructions
  uint32_t trace_start_pc;        // Start tracing from this PC
  uint32_t trace_end_pc;          // Stop tracing at this PC
} execution_tracer_t;

// Tracer management
bool tracer_init(execution_tracer_t* tracer, size_t capacity);
void tracer_destroy(execution_tracer_t* tracer);
void tracer_set_file_output(execution_tracer_t* tracer, const char* filename);

// Tracing functions
void trace_instruction_execution(execution_tracer_t* tracer, const cpu_state_t* cpu, const instruction_t* instruction, uint32_t result_data);
void print_trace_summary(const execution_tracer_t* tracer);
void print_recent_trace(const execution_tracer_t* tracer, size_t num_entries);

// Debug support
void debug_print_pipeline_contents(const cpu_state_t* cpu);
void debug_print_hazard_status(const cpu_state_t* cpu);

#endif // TRACE_H
