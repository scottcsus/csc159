// k-entry.S, entries to kernel services, build process trapframe

#include "k-const.h"
#include <spede/machine/asmacros.h> // do not use/include "spede.h"
#define K_STACK_SIZE (PROC_STACK_SIZE * 8) // kernel has 32KB stack

.comm k_stack, K_STACK_SIZE, 1      // declare kernel stack space (16K x 1B)
.text

// load proc trapframe to run it
ENTRY(Loader)
   mov 4(%esp), %ebx
   mov %ebx, %esp
   popa
   iret

  // copy 4 bytes from 4B above esp to ebx
  // copy ebx to esp (point esp to process trapframe)
  // pop all (8) registers
  // return from interrupt

// build proc trapframe, and go into kernel
ENTRY(TimerEntry)                  // will have efl, cs, eip pushed by hardware
   pusha
   mov %esp, %ebx
   movw $0x10, %ax                 // set kernel data segment registers
   mov %ax, %ds                    // set kernel data segment registers
   mov %ax, %es                    // set kernel data segment registers
   leal k_stack + K_STACK_SIZE, %esp  // set esp to top of kernel stack
   push %ebx			   //Push ebx (onto the kernel stack)
   cld			           //Clears the direction flag
   call CNAME(Kernel)

