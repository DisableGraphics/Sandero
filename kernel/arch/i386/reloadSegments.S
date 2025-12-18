.global reloadSegments
reloadSegments:
    # Far jump to reload CS
    ljmp $0x08, $.reload_CS

.reload_CS:
    # Load data segment selector into AX
    movw $0x10, %ax

    # Reload data segment registers
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    ret
