.intel_syntax noprefix
.global kernel_start, mem_in16
.extern _kernel_entry

# define STACK_SIZE             0x11000

.section .text
.code32
kernel_start:
        mov     %esp, stack_top

        push   0
        popf

        push   %ebx        #1st argument
        push   %eax        #2nd argument

        call    _kernel_entry
        mov     dword ptr [0xb8000], 0x0f4b0f4f

loop_infinite:
        hlt
        jmp     loop_infinite

mem_in16:
        mov     dword ptr [%edi], %esi 
        ret

.section .stack
stack_bottom:
        .skip   STACK_SIZE
stack_top:
        