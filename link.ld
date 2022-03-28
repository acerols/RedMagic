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
    . = . + 0x4000;
    sp_top = .;
 }
