#pragma once
#include <stdint.h>
struct Multiboot2Info {
	// Pointers to the relevant tags or nullptr if missing
	const struct multiboot_tag_mmap* memory_map;
	const struct multiboot_tag_module* modules;
	uint32_t modules_count;
	const struct multiboot_tag_string* cmdline;
	const struct multiboot_tag_framebuffer* fb;
	const void* last_module_address;
};

struct Multiboot2Info parse_multiboot2_info(const uint8_t* mb_info_ptr);