.set MULTIBOOT2_MAGIC, 0xe85250d6
.set ARCHITECTURE, 0
.set HEADER_ALIGN, 8

.section .multiboot.data, "a", @progbits
.align 8

multiboot_header:
	.long MULTIBOOT2_MAGIC                         # magic
	.long ARCHITECTURE                             # architecture
	.long multiboot_header_end - multiboot_header  # total header length
	.long -(MULTIBOOT2_MAGIC + ARCHITECTURE + (multiboot_header_end - multiboot_header))  # checksum

	# Information Request Tag (type 1)
	#.short 1                                       # tag type: INFORMATION_REQUEST
	#.short 0                                       # flags
	#.long 16                                       # size of this tag (header + 2 requests + padding)

	#.long 4                                        # request meminfo (tag type 4)
	#.long 8											# request framebuffer

	# Request Framebuffer
	#.short 5 # tag type: REQUEST_FRAMEBUFFER
	#.short 0 # flags
	#.long 24 # Size (2+2+4+4+4+4 = 20)
	#.long 0 # default width
	#.long 0 # default height
	#.long 0 # default bpp
	#.long 0

	# Padding to align to 8 bytes (2x4 bytes added above = 8 bytes, so already aligned)

	# End Tag (type 0)
	.long 0                                        # tag type: END
	.long 8                                        # size of end tag

multiboot_header_end:

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	push %eax
	push %ebx
	# Call the global constructors.
	call _init 

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
