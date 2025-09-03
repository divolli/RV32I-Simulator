#include "cpu/cpu_core.h"
#include "utils/defs.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//===========================================================================================
//                                MEMORY LIFECYCLE
//==========================================================================================

bool memory_init(memory_bank_t *memory, size_t size, uint32_t base_addr){
  if (!memory){  // Check for NULL argument
    fprintf(stderr, "Error: NULL argument in memory_init.\n");
    return false;
  }

  // Writing values
  memory->size = size;
  memory->base_address = base_addr;

  // Memory allocation
  memory->data = (uint8_t *) calloc(size, sizeof(uint8_t));
  if(!memory->data){ // Error Check
    fprintf(stderr, "Error: Memory allocation error in memory_init.\n");
    return false;
  }

  return true;
}


void memory_destroy(memory_bank_t *memory){
  if (!memory){  // Check for NULL argument
    fprintf(stderr, "Error: NULL argument in memory_destroy.\n");
    return;
  }

  // Free allocated memory
  free(memory->data);
  memory->data = NULL; // Set memory to null
}

//===========================================================================================
//                                CPU LIFECYCLE
//===========================================================================================

cpu_state_t* cpu_init(void) {
  // Creating main cpu struct
  cpu_state_t* cpu = (cpu_state_t *) calloc(1, sizeof(cpu_state_t));

  // check for memory error
  if (!cpu){
    fprintf(stderr, "Error: Allocating memory error in cpu_init.\n");
    return NULL;
  }

  return cpu;
}


void cpu_reset(cpu_state_t *cpu) {
  if (!cpu) {
    fprintf(stderr, "Error: NULL argument in cpu_reset.\n");
    return;
  }

  // Reset architectural state
  cpu->pc = 0;

  // Reset register file (x0 stays 0, others become 0)
  memset(&cpu->reg_file, 0, sizeof(register_file_t));

  // Reset pipeline registers
  memset(&cpu->if_id, 0, sizeof(if_id_register_t));
  memset(&cpu->id_ex, 0, sizeof(id_ex_register_t));
  memset(&cpu->ex_mem, 0, sizeof(ex_mem_register_t));
  memset(&cpu->mem_wb, 0, sizeof(mem_wb_register_t));

  // Reset pipeline control state
  cpu->pipeline_stalled = false;
  cpu->pipeline_flushed = false;
  cpu->stall_cycles = 0;

  // Reset performance counters
  cpu->total_cycles = 0;
  cpu->total_instructions = 0;
  cpu->pipeline_stalls = 0;
  cpu->branch_instructions = 0;
  cpu->branch_mispredictions = 0;

  // Reset debug state
  cpu->single_step_mode = false;
  cpu->trace_enabled = false;
  cpu->breakpoint_address = 0;
  cpu->breakpoint_enabled = false;

  // Clear memory contents but preserve allocation
  if (cpu->instruction_memory.data) {
    memset(cpu->instruction_memory.data, 0, cpu->instruction_memory.size);
  }
  if (cpu->data_memory.data) {
    memset(cpu->data_memory.data, 0, cpu->data_memory.size);
  }

}


void cpu_destroy(cpu_state_t *cpu){
  if (!cpu){  // Check for NULL argument
    fprintf(stderr, "Error: NULL argument in cpu_destry.\n");
    return;
  }

  memory_destroy(&cpu->data_memory);
  memory_destroy(&cpu->instruction_memory);
  free(cpu);
}

//===========================================================================================
//                                REGISTER FILE OPERATIONS
//===========================================================================================

uint32_t register_read(const cpu_state_t *cpu, uint8_t reg_num){
  if (!cpu || reg_num > 31){  // Check for NULL argument
    fprintf(stderr, "Error: NULL argument or reg_num is bigger than 31 in register_read.\n");
    return 0;
  }
  // Return register
  return cpu->reg_file.registers[reg_num];
}


void register_write(cpu_state_t *cpu, uint8_t reg_num, uint32_t value){
  if (!cpu){  // Check for NULL argument
    fprintf(stderr, "Error: NULL argument in register_write.\n");
    return;
  }
  if (reg_num == 0) return; // x0 always 0

  // Writing value to registers
  cpu->reg_file.registers[reg_num] = value;
}

//===========================================================================================
//                                DEBUG FUNCTIONS
//===========================================================================================

void print_cpu_state(const cpu_state_t* cpu){
  if (!cpu){  // Check for NULL argument
    fprintf(stderr, "Error: NULL argument in print_cpu_state.\n");
    return;
  }
  printf("PROGRAM COUNT          --- 0x%08x\n", cpu->pc);
  printf("TOTAL CYCLES           --- %lu\n", cpu->total_cycles);
  printf("TOTAL INSTRUCTIONS     --- %lu\n", cpu->total_instructions);
  printf("PIPELINE STALLS        --- %lu\n", cpu->pipeline_stalls);
  printf("BRANCH INSTRUCTIONS    --- %lu\n", cpu->branch_instructions);
  printf("BRANCH MISPREDICTIONS  --- %lu\n", cpu->branch_mispredictions);
  printf("PIPELINE STALLED       --- %s\n", cpu->pipeline_stalled ? "true" : "false");
  printf("PIPELINE FLUSHED       --- %s\n", cpu->pipeline_flushed ? "true" : "false");
}


void print_register_file(const cpu_state_t* cpu){
  if (!cpu){  // Check for NULL argument
    fprintf(stderr, "Error: NULL argument in print_register_file.\n");
    return;
  }
  // Registers name array
  static const char* reg_name[32] = {
    "zero","ra","sp","gp","tp","t0","t1","t2",
    "s0","s1","a0","a1","a2","a3","a4","a5",
    "a6","a7","s2","s3","s4","s5","s6","s7",
    "s8","s9","s10","s11","t3","t4","t5","t6"
  };

  printf("Name  (Reg)   Value\n");
  printf("----  -----   -----\n");
  for (int i = 0; i < NUM_REGISTERS; ++i){
    uint32_t reg = cpu->reg_file.registers[i];
    printf("%-5s (x%02d): 0x%08x\n", reg_name[i], i, reg);
  }
}


void print_pipeline_state(const cpu_state_t* cpu) {
  if (!cpu) {
    fprintf(stderr, "Error: NULL argument in print_pipeline_state.\n");
    return;
  }

  printf("PIPELINE STATE\n");
  printf("==============\n");

  // IF/ID
  printf("IF/ID  : PC = 0x%08x | Instr = 0x%08x | Valid = %d | Stalled = %d\n",
    cpu->if_id.pc,
    cpu->if_id.instruction,
    cpu->if_id.valid,
    cpu->if_id.stalled
  );

  // ID/EX
  printf("ID/EX  : PC = 0x%08x | Valid = %d | Stalled = %d | Imm = 0x%08x\n",
    cpu->id_ex.pc,
    cpu->id_ex.valid,
    cpu->id_ex.stalled,
    cpu->id_ex.immediate
  );

  // EX/MEM
  printf("EX/MEM : PC = 0x%08x | Valid = %d | ALU = 0x%08x | Zero = %d | BranchTaken = %d\n",
    cpu->ex_mem.pc,
    cpu->ex_mem.valid,
    cpu->ex_mem.alu_result,
    cpu->ex_mem.alu_zero,
    cpu->ex_mem.branch_taken
  );

  // MEM/WB
  printf("MEM/WB : Valid = %d | ALU = 0x%08x | MemData = 0x%08x | PC+4 = 0x%08x\n",
    cpu->mem_wb.valid,
    cpu->mem_wb.alu_result,
    cpu->mem_wb.memory_data,
    cpu->mem_wb.pc_plus_4
  );

  printf("--------------\n");
}

