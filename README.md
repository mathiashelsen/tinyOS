# tinyOS
A tiny OS

Objectives:
 - Multi-tasking with preemptive round-robin scheduler
 - Memory management
 - Use good old GCC

# What's here
Currently I'm investigating how everything is glued together by GCC. This little bugger does quite a lot of work behind the scenes.

# What I've learned

- BSS comes right after .text, it is addressed from PC+relative offset
- Stack is never addressed directly, i.e. the OS can set it up before running the entry point
- Heap (not used in the current code) follows BSS. It is to be expected that the C code will expect
the heap-address to be fixed at compile time. However, we will write malloc, so, the heap address will be at
_bss_end + 1, BUT we will let the compiler set this!
- Global shared variables, will be put in _sdata, and the address is hard coded! In the objdump, you can find references to 0x200... for variable j, which is the start of the RAM. Ergo, at compile time, the SOB assumes and absolute address for its data.

# Todo's

- Starting a new function is done correctly: we push initialization stuff onto the stack in scheduler.c (including lr=0xfff..9), then the interrupt handler in tinyOS.c puts this lr back to PC and the hardware initializes the new function correctly
- Restorting a function doesnt work: we restore the registers, but lr is not set correctly.
- Solution: remove push lr in tinyOS.c ISR, always push lr 0xff...9 inside scheduler.c
