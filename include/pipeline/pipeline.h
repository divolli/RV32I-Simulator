#ifndef PIPELINE_H
#define PIPELINE_H

#include "cpu/cpu_core.h"

// Pipeline execution functions - one per stage
void pipeline_stage_fetch(cpu_state_t* cpu);
void pipeline_stage_decode(cpu_state_t* cpu);
void pipeline_stage_execute(cpu_state_t* cpu);
void pipeline_stage_memory(cpu_state_t* cpu);
void pipeline_stage_writeback(cpu_state_t* cpu);

// Main pipeline control
void pipeline_clock_cycle(cpu_state_t* cpu);
void pipeline_flush(cpu_state_t* cpu);
void pipeline_stall(cpu_state_t* cpu, uint32_t cycles);

// Hazard detection and resolution
bool detect_data_hazard(const cpu_state_t* cpu);
bool detect_load_use_hazard(const cpu_state_t* cpu);
bool detect_control_hazard(const cpu_state_t* cpu);
void resolve_hazards(cpu_state_t* cpu);

#endif // PIPELINE_H
