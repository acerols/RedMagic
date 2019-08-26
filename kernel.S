.intel_syntax noprefix
.global kernel_start
.extern _kernel_entry


.section .text
.code32
kernel_start:
        push   0
        popf

        push   %ebx        #1st argument
        push   %eax        #2nd argument

        call    _kernel_entry
        mov     dword ptr [0xb8000], 0x2f4b2f4b

loop_infinite:
        hlt
        jmp     loop_infinite