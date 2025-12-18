#include <kernel/syscalls.h>
#include <kernel/sched.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
	uint16_t    isr_low;
	uint16_t    kernel_cs;
	uint8_t     reserved;
	uint8_t     attributes;
	uint16_t    isr_high;
} __attribute__((packed)) idt_entry_t;

__attribute__((aligned(0x10))) 
static idt_entry_t idt[256];

typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;
extern void int80h();

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08;
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->reserved       = 0;
}

void setup_syscalls() {
	idtr.base = (int)(&idt);
	idtr.limit = (int)(sizeof(idt)-1);
	__asm __volatile("lidt %0" : : "m"(idtr));
	idt_set_descriptor(0x9E, &int80h, 0x8E);
}

int syscall_handler(size_t syscallno, size_t arg0, size_t arg1) {
	switch(syscallno) {
		case 0:
			scheduler_exit_current_task();
		case 1:
			scheduler_create_task((void (*)(void)) arg0, (void *) arg1);
		case 2:
			scheduler_relinquish();
		default:
			return -1;
	};
	return 0;
}