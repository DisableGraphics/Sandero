cmake_minimum_required(VERSION 3.20)
project(SanderoUser)

set(CMAKE_ASM_FLAGS "-g -ffreestanding -nostdlib -mgeneral-regs-only -lgcc")
set(CMAKE_C_FLAGS "-g -ffreestanding -nostdlib -mgeneral-regs-only -lgcc")

add_subdirectory(vga_test)