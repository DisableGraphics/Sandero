.extern syscall_handler
.global int80h
int80h:
	push %ebp
	push %edi
	push %esi
	push %ebx

	push %edx
	push %ecx
	push %eax
	call syscall_handler
	add $4,%esp
	pop %ecx
	pop %edx

	pop %ebx
	pop %esi
	pop %edi
	pop %ebp
	iret