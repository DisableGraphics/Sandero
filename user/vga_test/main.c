#include "tty.h"

void _start() {
	terminal_initialize();
	
	terminal_putchar('H');
	terminal_putchar('e');
	terminal_putchar('l');
	terminal_putchar('l');
	terminal_putchar('o');
	while(1) __asm __volatile(
		"mov $0,%eax\n"
		"int $0x9e\n"
	);
}