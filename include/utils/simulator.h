#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "cpu/cpu_core.h"
#include "trace.h"

// Simulator configuration
typedef struct {
    uint64_t max_cycles;            // Maximum cycles to simulate (0 = unlimited)
    uint32_t max_instructions;      // Maximum instructions (0 = unlimited)
    bool enable_tracing;            // Enable instruction tracing
    bool enable_pipeline_debug;     // Enable pipeline state debugging
    bool single_step;               // Single-step execution mode
    bool break_on_ecall;            // Break execution on ECALL
    bool break_on_ebreak;           // Break execution on EBREAK
} simulator_config_t;

// Complete simulator state
typedef struct {
    cpu_state_t cpu;                // CPU core
    execution_tracer_t tracer;      // Execution tracer
    simulator_config_t config;      // Configuration

    // Execution control
    bool running;                   // Simulator is running
    bool paused;                    // Execution is paused
    uint32_t exit_code;             // Program exit code

    // Performance metrics
    uint64_t start_time;            // Simulation start time (for wall clock)
    double simulation_time_seconds; // Total simulation wall time
    double instructions_per_second; // IPS performance metric
} simulator_t;

// Simulator lifecycle
bool simulator_init(simulator_t* sim, const simulator_config_t* config);
void simulator_destroy(simulator_t* sim);

// Program loading
bool simulator_load_program(simulator_t* sim, const char* filename);
bool simulator_load_binary(simulator_t* sim, const uint32_t* program, size_t size);

// Execution control
void simulator_run(simulator_t* sim);
void simulator_step(simulator_t* sim);
void simulator_pause(simulator_t* sim);
void simulator_reset(simulator_t* sim);

// Status and debugging
void simulator_print_status(const simulator_t* sim);
void simulator_print_performance_stats(const simulator_t* sim);

// Interactive debugging
void simulator_interactive_mode(simulator_t* sim);

#endif // SIMULATOR_H
