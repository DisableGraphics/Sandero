cmake_minimum_required(VERSION 3.20)
project(Bastion)

set(EXEC_NAME sandero)

enable_language(ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_ASM_FLAGS "-g -fno-pie -no-pie")
set(CMAKE_C_FLAGS "-g -static-libgcc -O2 -ffreestanding -nostdlib -lgcc")


# Add subdirectories for kernel and libc
add_subdirectory(kernel)
add_subdirectory(libc)

add_executable(${EXEC_NAME})

target_sources(${EXEC_NAME} PRIVATE
    $<TARGET_OBJECTS:kernel_obj>
    $<TARGET_OBJECTS:libc_obj>
)

target_link_options(${EXEC_NAME} PRIVATE -T ${CMAKE_SOURCE_DIR}/kernel/arch/i386/linker.ld)

add_subdirectory(user)