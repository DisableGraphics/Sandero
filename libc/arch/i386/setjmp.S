.global setjmp
setjmp:
	mov (%esp),%eax 		// EIP of call into EAX
	mov 4(%esp),%ecx 		// Parameter buf into ecx
	mov %eax,0(%ecx) 		// Add EIP to jmp_buf
	mov %ebx,8(%ecx) 		// Rest of registers (EBX, ESI, EDI, EBP)
	mov %esi,12(%ecx)
	mov %edi,16(%ecx)
	mov %ebp,20(%ecx)
	lea 4(%esp), %eax 		// Push the correct ESP (not really the current one)
	mov %eax,4(%ecx) 
	xor %eax,%eax
	ret