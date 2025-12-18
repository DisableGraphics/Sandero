#include "multiboot/multiboot2.h"
#include <kernel/gdt.h>
#include <kernel/syscalls.h>
#include <kernel/sched.h>
#include <kernel/multibootparser.h>
#include <kernel/alloc.h>
#include <stdint.h>

void kernel_main(uintptr_t mbd, unsigned int _) {
	setup_gdt();
	setup_syscalls();
	init_alloc();
	scheduler_init();
	struct Multiboot2Info inf = parse_multiboot2_info((const uint8_t*)(mbd));
	scheduler_create_task((void (*)(void))(inf.modules[0].mod_start), (void*)(10485760));
	scheduler_run();
}
