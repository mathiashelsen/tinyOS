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
