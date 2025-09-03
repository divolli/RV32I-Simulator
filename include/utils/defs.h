#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Memory and register constants
#define NUM_REGISTERS 32
#define INSTRUCTION_MEMORY_SIZE (64 * 1024)  // 64KB instruction memory
#define DATA_MEMORY_SIZE (64 * 1024)         // 64KB data memory
// #define REGISTER_WIDTH 32
// #define INSTRUCTION_WIDTH 32

// Memory alignment
#define WORD_ALIGN_MASK 0xFFFFFFFC
#define HALFWORD_ALIGN_MASK 0xFFFFFFFE

// Instruction opcodes (bits 6:0) - matches real RV32I specification
#define OPCODE_LUI      0x37
#define OPCODE_AUIPC    0x17
#define OPCODE_JAL      0x6F
#define OPCODE_JALR     0x67
#define OPCODE_BRANCH   0x63
#define OPCODE_LOAD     0x03
#define OPCODE_STORE    0x23
#define OPCODE_OP_IMM   0x13  // I-type arithmetic
#define OPCODE_OP       0x33  // R-type arithmetic
#define OPCODE_MISC_MEM 0x0F  // FENCE
#define OPCODE_SYSTEM   0x73  // ECALL, EBREAK

// Funct3 values for arithmetic operations
#define FUNCT3_ADD_SUB  0x0
#define FUNCT3_SLL      0x1
#define FUNCT3_SLT      0x2
#define FUNCT3_SLTU     0x3
#define FUNCT3_XOR      0x4
#define FUNCT3_SRL_SRA  0x5
#define FUNCT3_OR       0x6
#define FUNCT3_AND      0x7

// Funct3 values for loads and stores
#define FUNCT3_BYTE     0x0  // LB, SB
#define FUNCT3_HALF     0x1  // LH, SH
#define FUNCT3_WORD     0x2  // LW, SW
#define FUNCT3_BYTE_U   0x4  // LBU (unsigned byte)
#define FUNCT3_HALF_U   0x5  // LHU (unsigned halfword)

// Funct3 values for branches
#define FUNCT3_BEQ      0x0
#define FUNCT3_BNE      0x1
#define FUNCT3_BLT      0x4
#define FUNCT3_BGE      0x5
#define FUNCT3_BLTU     0x6
#define FUNCT3_BGEU     0x7

// Funct7 values for distinguishing operations
#define FUNCT7_NORMAL   0x00  // ADD, SLL, SRL, etc.
#define FUNCT7_ALT      0x20  // SUB, SRA

// System instruction immediate values
#define SYSTEM_ECALL    0x000
#define SYSTEM_EBREAK   0x001

// Instruction format types
typedef enum {
  FORMAT_R,  // Register-register operations
  FORMAT_I,  // Immediate operations, loads, JALR
  FORMAT_S,  // Stores
  FORMAT_B,  // Branches
  FORMAT_U,  // Upper immediate (LUI, AUIPC)
  FORMAT_J   // Jump (JAL)
} instruction_format_t;

// All 47 RV32I instructions
typedef enum {
  // R-type arithmetic (10 instructions)
  INST_ADD, INST_SUB, INST_SLL, INST_SLT, INST_SLTU,
  INST_XOR, INST_SRL, INST_SRA, INST_OR, INST_AND,

  // I-type immediate arithmetic (9 instructions)
  INST_ADDI, INST_SLTI, INST_SLTIU, INST_XORI, INST_ORI, INST_ANDI,
  INST_SLLI, INST_SRLI, INST_SRAI,

  // I-type loads (5 instructions)
  INST_LB, INST_LH, INST_LW, INST_LBU, INST_LHU,

  // I-type jump (1 instruction)
  INST_JALR,

  // S-type stores (3 instructions)
  INST_SB, INST_SH, INST_SW,

  // B-type branches (6 instructions)
  INST_BEQ, INST_BNE, INST_BLT, INST_BGE, INST_BLTU, INST_BGEU,

  // U-type upper immediate (2 instructions)
  INST_LUI, INST_AUIPC,

  // J-type jump (1 instruction)
  INST_JAL,

  // System instructions (2 instructions)
  INST_ECALL, INST_EBREAK,

  // Memory ordering (1 instruction)
  INST_FENCE,

  // Special states
  INST_NOP,     // Internally used for pipeline bubbles
  INST_INVALID  // Illegal instruction
} instruction_type_t;

// ALU operation types - matches typical processor ALU design
typedef enum {
  ALU_ADD,
  ALU_SUB,
  ALU_AND,
  ALU_OR,
  ALU_XOR,
  ALU_SLL,    // Shift left logical
  ALU_SRL,    // Shift right logical
  ALU_SRA,    // Shift right arithmetic
  ALU_SLT,    // Set less than (signed)
  ALU_SLTU,   // Set less than unsigned
  ALU_COPY_A, // Pass input A through
  ALU_COPY_B  // Pass input B through
} alu_operation_t;

// Memory operation types
typedef enum {
  MEM_NOP,    // No memory operation
  MEM_READ,   // Memory read (loads)
  MEM_WRITE   // Memory write (stores)
} memory_operation_t;

// Memory access sizes
typedef enum {
  MEM_SIZE_BYTE,
  MEM_SIZE_HALFWORD,
  MEM_SIZE_WORD
} memory_size_t;

// Branch condition evaluation results
typedef enum {
  BRANCH_NOT_TAKEN,
  BRANCH_TAKEN
} branch_result_t;

#endif // DEFS_H
