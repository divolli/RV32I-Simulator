#include "cpu/cpu.h"
#include <assert.h>

int main(void){
  cpu_state_t* cpu = cpu_create();
  cpu_write_register(cpu, 1, 0x12345678);
  assert(cpu_read_register(cpu, 1) == 0x12345678);
  assert(cpu_read_register(cpu, 0) == 0);
  return 0;
}
