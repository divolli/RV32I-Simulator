#ifndef HAZARDS_H
#define HAZARDS_H

#include "cpu/cpu_core.h"

// Data forwarding sources
typedef enum {
  FORWARD_NONE,           // No forwarding needed
  FORWARD_FROM_EX_MEM,    // Forward from EX/MEM stage
  FORWARD_FROM_MEM_WB     // Forward from MEM/WB stage
} forwarding_source_t;

// Forwarding control signals
typedef struct {
  forwarding_source_t forward_rs1; // Forwarding for rs1
  forwarding_source_t forward_rs2; // Forwarding for rs2
  uint32_t forward_rs1_data;       // Actual forwarded data for rs1
  uint32_t forward_rs2_data;       // Actual forwarded data for rs2
} forwarding_unit_t;

// Hazard detection functions
bool has_raw_hazard(const cpu_state_t* cpu, uint8_t source_reg);
bool has_load_use_hazard(const cpu_state_t* cpu);
bool has_control_hazard(const cpu_state_t* cpu);

// Forwarding unit
forwarding_unit_t compute_forwarding_signals(const cpu_state_t* cpu);
uint32_t get_forwarded_register_data(const cpu_state_t* cpu, uint8_t reg_num, forwarding_source_t forward_source);

#endif // HAZARDS_H
