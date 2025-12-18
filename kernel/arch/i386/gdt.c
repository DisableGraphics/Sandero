#include <stdint.h>
#include <kernel/gdt.h>

static uint64_t gdt[] = {
	0,
	0x00CF9A000000FFFF,
	0x00CF92000000FFFF,
};

struct __attribute__((packed)) gdtr {
    uint16_t limit;
    uint32_t base;
};

static struct gdtr gdtr = {
	sizeof(gdt)-1,
	(uint32_t)(&gdt)
};

//static uint8_t tss[0x6c];

extern void reloadSegments();
void setup_gdt() {
	__asm __volatile("lgdt %0" : : "m"(gdtr));
	reloadSegments();
}