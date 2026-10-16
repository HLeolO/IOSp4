cmake_minimum_required(VERSION 3.20)
project(PS4EmuCore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ps4emu_core STATIC
  Core/Bridge/ps4emu_c.cpp
  Core/Loader/ElfLoader.cpp)
target_include_directories(ps4emu_core PUBLIC Core)
target_compile_options(ps4emu_core PRIVATE -Wall -Wextra)

option(PS4EMU_BUILD_TESTS "Compilar testes do núcleo (no host)" ON)
if(PS4EMU_BUILD_TESTS)
  enable_testing()
  add_executable(ps4emu_tests Tests/test_core.cpp)
  target_link_libraries(ps4emu_tests PRIVATE ps4emu_core)
  add_test(NAME core COMMAND ps4emu_tests)
endif()
