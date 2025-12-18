target_sources(kernel_obj PRIVATE 
	boot.S
	crti.S
	crtn.S
	int80h.S
	reloadSegments.S
	syscalls.c
	gdt.c
	)
