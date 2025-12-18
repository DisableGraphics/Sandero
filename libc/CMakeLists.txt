# Build libc object files
add_library(libc_obj STATIC)

target_compile_options(libc_obj PRIVATE "-D__is_libk -fno-asynchronous-unwind-tables -fno-exceptions -ffreestanding -nostdlib -lgcc")

add_subdirectory(string)
add_subdirectory(stdlib)
add_subdirectory(arch)

# Include libc headers
target_include_directories(libc_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include kernel headers for compilation
target_include_directories(libc_obj PRIVATE ${CMAKE_SOURCE_DIR}/kernel/include)
