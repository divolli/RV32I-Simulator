#ifndef ALU_H
#define ALU_H

#include "utils/defs.h"

// ALU result structure
typedef struct {
    uint32_t result;                // Primary result
    bool zero;                      // Result is zero
    bool negative;                  // Result is negative (MSB set)
    bool carry_out;                 // Carry out from MSB
    bool overflow;                  // Signed overflow occurred
} alu_result_t;

// ALU operations
alu_result_t alu_execute(alu_operation_t operation, uint32_t a, uint32_t b);

// Branch condition evaluation
bool evaluate_branch_condition(uint8_t funct3, uint32_t rs1_data, uint32_t rs2_data);

// Address calculations
uint32_t calculate_branch_target(uint32_t pc, int32_t immediate);
uint32_t calculate_jump_target(uint32_t pc, int32_t immediate);
uint32_t calculate_jump_register_target(uint32_t rs1_data, int32_t immediate);

#endif // ALU_H
