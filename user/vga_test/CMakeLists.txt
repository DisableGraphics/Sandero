cmake_minimum_required(VERSION 3.20)
project(flatbin C ASM)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

add_executable(vga_test
	main.c
	vga.c
)

target_compile_options(vga_test PRIVATE
	-ffreestanding
	-fno-stack-protector
	-fno-builtin
)

target_link_options(vga_test PRIVATE
	-nostdlib
	-nodefaultlibs
	-T ${CMAKE_SOURCE_DIR}/user/common/linker.ld
)

# add_custom_command(
# 	TARGET vga_test POST_BUILD
# 	COMMAND ${CMAKE_OBJCOPY} -O binary
# 			$<TARGET_FILE:vga_test>
# 			${CMAKE_BINARY_DIR}/vga_test.bin
# )
