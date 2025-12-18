.global longjmp
longjmp:
	mov 4(%esp),%ecx // buf into ecx
	mov 8(%esp),%edx // ret into edx
	// Load registers EBX, ESI, EDI, EBP & ESP.
	// they don't need calculations
	mov 8(%ecx),%ebx
	mov 12(%ecx),%esi
	mov 16(%ecx),%edi
	mov 20(%ecx),%ebp
	mov 4(%ecx),%esp
	// Return value into eax
	mov %edx,%eax
	// Restore EIP with some jmp fuckery
	jmp *0(%ecx)