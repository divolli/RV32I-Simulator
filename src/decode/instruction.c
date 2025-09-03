#include "decode/instructions.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


instruction_t* create_instruction(uint32_t word){
  instruction_t* instr = (instruction_t *) calloc(1, sizeof(instruction_t));

  // Error check
  if(!instr){
    fprintf(stderr, "Error memory allocation\n");
    return NULL;
  }

  instr->word = word;
  return instr;
}


void destroy_instruction(instruction_t* instr){
  if (!instr) return;
  free(instr);
}


void print_instruction(instruction_t* instr){
  if(!instr){
    fprintf(stderr, "Error Invalid input\n");
    return;
  }

  //Getting opcode
  uint32_t opcode = instr->r_type.opcode;

  switch(opcode){
    case OP_RTYPE:
      // Check function code for R-type
      switch(instr->r_type.funct){
        case FUNCT_ADD:
          // Format: ADD $rd, $rs, $rt
          printf("ADD $%d, $%d, $%d", instr->r_type.rd, instr->r_type.rs, instr->r_type.rt);
          break;
        case FUNCT_SUB:
          // Format: SUB $rd, $rs, $rt
          printf("SUB $%d, $%d, $%d", instr->r_type.rd, instr->r_type.rs, instr->r_type.rt);
          break;
        case FUNCT_AND:
          // Format: AND $rd, $rs, $rt
          printf("AND $%d, $%d, $%d", instr->r_type.rd, instr->r_type.rs, instr->r_type.rt);
          break;
        case FUNCT_OR:
          // Format: OR $rd, $rs, $rt
          printf("OR $%d, $%d, $%d", instr->r_type.rd, instr->r_type.rs, instr->r_type.rt);
          break;
        // add more funct
      }
      break;
    case OP_ADDI:
      // Format: ADDI $rt, $rs, immediate
      int16_t signed_imm = (int16_t)instr->i_type.immediate;
      printf("ADDI $%d, $%d, %d", instr->i_type.rt, instr->i_type.rs, signed_imm);
      break;
    case OP_LW:
      // Format: LOAD WORD $rt, $rs, immediate
      printf("LW $%d, $%d($%d)", instr->i_type.rt, instr->i_type.rs, instr->i_type.immediate);
      break;
    case OP_SW:
      // Format: STORE WORD $rt, $rs, immediate
      printf("SW $%d, $%d($%d)", instr->i_type.rt, instr->i_type.rs, instr->i_type.immediate);
      break;
    case OP_BEQ:
      // Format: BRANCH IF EQUAL $rt, $rs, immediate
      printf("BEQ $%d, $%d, $%d", instr->i_type.rt, instr->i_type.rs, instr->i_type.immediate);
      break;
    case OP_J:
      // Format: JUMP $address
      printf("J %d", instr->j_type.address);
      break;
    // add more opcodes
    default:
      printf("UNKNOWN");
      return;
  }

  printf("\n");
}
