OUTPUT_ARCH("riscv")
 ENTRY(_start)
 SECTIONS
 {
    . = 0x80000000;
    test0 : { boot.o(.text) }
    .text : { *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    .sdata : { *(.sdata) }
    PROVIDE(_bss_start = .);
    .bss : { *(.bss) }
    .sbss : { *(.sbss) }
    PROVIDE(_bss_end = .);
    . = ALIGN(8);
    heap_space = .;
    . = . + 0x10000;
    heap_space_end = .;
    kernel_stack_end = .;
    . = . + 0x10000;
    sp_top = .;
    kernel_stack_start = .;
    trap_stack_end = .;
    . = . + 0x10000;
    trap_stack_start = .;

}
