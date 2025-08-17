cmake_minimum_required(VERSION 3.10)
project(risc_simulator C)

set(CMAKE_C_STANDART 99)
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")


add_executable(risc
  main.c
  # will add more as i go
)

find_program(VALGRIND valgrind)
if(VALGRIND)
  add_custom_target(memcheck
    COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all
      --track-origins=yes --verbose $<TARGET_FILE: risc_sim>
  )
endif()
