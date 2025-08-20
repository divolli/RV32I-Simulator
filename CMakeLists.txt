cmake_minimum_required(VERSION 3.10)
project(risc_simulator C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")

file(GLOB_RECURSE SOURCES "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable(risc
  ${SOURCES}
)

target_include_directories(risc
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

find_program(VALGRIND valgrind)
if(VALGRIND)
  add_custom_target(memcheck
    COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all
      --track-origins=yes --verbose $<TARGET_FILE:risc>
  )
endif()
