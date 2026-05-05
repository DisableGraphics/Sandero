# Sandero
The _essence_ of an OS.

## What the hell is this
First of all, this is what cloc has to say about this project:
```
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C/C++ Header                     6             70             32            369
C                                7             47             21            263
Assembly                         5             20             28             79
Linker Script                    1              6             14             23
CMake                            4              3              2             22
-------------------------------------------------------------------------------
SUM:                            23            146             97            756
-------------------------------------------------------------------------------
```
What I present, ladies and gentlemen, is a full kernel made in ~760 LOC and in ~5 hours for x86.*

*756 lines of code only in the kernel/ folder. libc includes some required functions (like memcpy/memmove) for the compiler and setjmp/longjmp.

## Kernel design
Of course there is a trick here:
- No virtual memory
- No interrupts
- No timers
- Cooperative multitasking
- All tasks run in ring 0
- No fs
- No nothing
The kernel only implements 5 things:
- Process allocation
- System calls
- Scheduler
- Loading one program (and a flat executable at that) via a multiboot module
- GDT
Of which the last one (GDT setup) only exists because Multiboot puts the GDT in an undefined state.

## Is that a kernel?
Yes. Specifically a [Megalithic kernel](https://wiki.osdev.org/Megalithic_Kernel).

## Is this actually usable?
Right now no.
However, since all functionality is done in "user space" (ring 0 tasks) you can technically write a full OS.

## How to compile
```
chmod +x cross-compiler.sh
./cross-compiler.sh
./qemu.sh
```
