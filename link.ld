ENTRY(kernel_start)

SECTIONS{
    . = 1M;

    .text :
    {
        _text_start = .;
        *(.multiboot_header)
        *(.text)
        _text_end = .;
    }
    
    .rodata :
    {
        _rodata_start = .;
        *(.rodata)
        _rodata_end = .;
    }

    .data :
    {
        _data_start = .;
        *(.data)
        _data_end = .;
    }

    .bss :
    {
        _bss_start = .;
        *(.bss)
        _bss_end = .;
    }
    .stack :
    {
        _stack_start = .;
        *(.stack)
        _stack_end = .;
    }
}
