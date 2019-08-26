# define STACK_SIZE

.section .multiboot_header
.align 8
header_start:
    .long 0xe85250d6
    .long 0
    .long header_end - header_start
    #checksum
    .long 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    #insert optional multiboot tags header_end
    
    #required end tag

    .word 0     # type
    .word 0     # flags 
    .long 8     # size

header_end:
