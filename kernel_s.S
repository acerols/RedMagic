.intel_syntax   noprefix
//.att_syntax
.global kernel_start, mem_in16
.global errors 
.extern _kernel_entry

// syntax mov a, b a -> b

# define STACK_SIZE             0x11000

.section .text
.code32
kernel_start:
        mov     %esp, stack_top

check_multiboot:
        cmp     %eax, 0x36d76289
        jne     .no_multiboot

check_cpuid:
        xor     %eax, %eax
        pushf
        pop     %eax

        mov     %eax, %ecx
        
        xor     %eax, (1 << 21)
        push    %eax
        popf

        pushf
        pop     %eax
        
        push    %ecx
        popf

        xor     %eax, %ecx
        jz      .no_cpuid

check_long_mode:
        xor     %eax, %eax
        mov     %eax, 0x80000000
        cpuid
        cmp     %eax, 0x80000001
        jb      .no_long_mode

set_up_page_table:
        mov     %eax, p3_table
        or      %eax, 0b11
        mov     [p4_table], %eax

        mov     %eax, p2_table
        or      %eax, 0b11
        mov     [p3_table], %eax

        xor     %ecx, %ecx
.map_p2_table:
        mov     %eax, 0x200000
        mul     %ecx
        or      %eax, 0b10000011
        mov     [p2_table + ecx * 8], %eax

        inc     %ecx
        cmp     %ecx, 512
        jne     .map_p2_table

enable_paging:
        mov     %eax, p4_table
        mov     %eax, %cr3

        mov     %cr4, %eax
        or      %eax, (1 << 5)
        mov     %eax, %cr4

        mov     %ecx, 0xC0000080
        rdmsr
        or      %eax, (1 << 8)
        wrmsr

        mov     %cr0, %eax
        or      %eax, (1 << 31)
        mov     %eax, %cr0

        lgdt    [gdtr]

.code64
long_mode_start:
        //pushb   0
        //popf

        /*pushl   %ebx            #1st argument
        pushl   %eax            #2nd argument


        mov     dword ptr [0xb8000], 0x0f4b0f4f
/*        movl    $(0x0f4b0f4f), 0xb8000
        //lea       0xb8000, $(0x0f4b0f4f)
        //lead     $(0x0f4b0f4f), (0xb8000)*/
        //movq    %rax, 0x2f592f412f4b2f4f

        mov     %ax, 0
        mov     %ax, %ss
        mov     %ax, %ds
        mov     %ax, %es
        mov     %ax, %fs
        mov     %ax, %gs

        xor     %rax, %rax
        movq    %rax, 0x000000000f4b0f50
        movq    qword [0xb8000], %rax
        movq    %rax, 0x000000000f410f59
        movq    qword [0xb8004], %rax
        call    _kernel_entry
        

loop_infinite:
        hlt
        jmp     loop_infinite

mem_in16:
        //mov     dword ptr [%edi], %esi 
        ret
.no_multiboot:
        mov     %al, 0x30       //error code 0
        jmp     errors
.no_cpuid:
        mov     %al, 0x31       //error code 1
        jmp     errors
.no_long_mode:
        mov     %al, 0x32

errors:
        //mov dword ptr [ 0xb8000 ], 0x4f524f45
        //mov dword ptr [ 0xb8004 ], 0x4f3a4f52
        //mov dword ptr [ 0xb8008 ], 0x4f204f20
        //mov byte ptr [ 0xb800a ], %al
        hlt

.section .data
.balign 8
.balign 8
gdt_desc:
                // null descriptor
        .quad 0
        .quad 0
        .quad 0x00209a0000000000  // code descriptor
        .quad 0x0000920000000000  // data descriptor
        .word 0
gdtr:
        .word 8*4 - 1
        .quad gdt_desc

.section .bss
.align  4096
p4_table:
        .skip   4096
p3_table:
        .skip   4096
p2_table:
        .skip   4096

.section .stack
stack_bottom:
        .skip   STACK_SIZE
stack_top:
        