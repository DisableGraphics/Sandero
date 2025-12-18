# the name of the target operating system
set(CMAKE_SYSTEM_NAME Sandero)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER   ${CMAKE_SOURCE_DIR}/cross/bin/i686-elf-gcc)
set(CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/cross/bin/i686-elf-g++)
set(CMAKE_C_COMPILER_LINKER ${CMAKE_SOURCE_DIR}/cross/bin/i686-elf-gcc)
set(CMAKE_CXX_COMPILER_LINKER ${CMAKE_SOURCE_DIR}/cross/bin/i686-elf-g++)
set(CMAKE_LINKER ${CMAKE_SOURCE_DIR}/cross/bin/i686-elf-ld)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH  ${CMAKE_SOURCE_DIR}/cross)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Avoid CMake's default test for the compiler
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)


