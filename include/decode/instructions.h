#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>

// Instructions
typedef union {
    uint32_t word;                // Raw 32-bit instruction

    // R-type: register operations (ADD, SUB, AND, OR, etc.)
    struct {
        uint32_t funct  : 6;      // Function code (bits 0-5)
        uint32_t shamt  : 5;      // Shift amount (bits 6-10)
        uint32_t rd     : 5;      // Destination register (bits 11-15)
        uint32_t rt     : 5;      // Target register (bits 16-20)
        uint32_t rs     : 5;      // Source register (bits 21-25)
        uint32_t opcode : 6;      // Operation code (bits 26-31)
    } r_type;

    // I-type: immediate operations (ADDI, LW, SW, BEQ, etc.)
    struct {
        uint32_t immediate : 16;  // Immediate value (bits 0-15)
        uint32_t rt        : 5;   // Target register (bits 16-20)
        uint32_t rs        : 5;   // Source register (bits 21-25)
        uint32_t opcode    : 6;   // Operation code (bits 26-31)
    } i_type;

    // J-type: jump operations (J, JAL)
    struct {
        uint32_t address : 26;    // Jump address (bits 0-25)
        uint32_t opcode  : 6;     // Operation code (bits 26-31)
    } j_type;
} instruction_t;

// Instruction opcodes
#define OP_RTYPE    0x00    // R-type operations
#define OP_ADDI     0x08    // Add immediate
#define OP_LW       0x23    // Load word
#define OP_SW       0x2B    // Store word
#define OP_BEQ      0x04    // Branch if equal
#define OP_J        0x02    // Jump

// R-type function codes
#define FUNCT_ADD   0x20    // Add
#define FUNCT_SUB   0x22    // Subtract
#define FUNCT_AND   0x24    // Bitwise AND
#define FUNCT_OR    0x25    // Bitwise OR

// Function declarations
instruction_t decode_instruction(uint32_t word);
const char* get_instruction_name(instruction_t instr);
void print_instruction(instruction_t instr);

#endif
