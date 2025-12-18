ENTRY(_start)
OUTPUT_FORMAT("binary")

SECTIONS {
  . = 0x0000;
  .text : { *(.text*) }
  .rodata : { *(.rodata*) }
  .data : { *(.data*) }
  .bss : { *(.bss*) }
}
