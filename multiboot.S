#define ASM_FILE
#include <multiboot2.h>

.section .multiboot_header
.align 8
header_start:
    .long MULTIBOOT2_HEADER_MAGIC
    .long 0
    .long header_end - header_start
    #checksum
    .long 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    #insert optional multiboot tags header_end
    
    .balign 8
align_tag:
    .short 6
    .short 0
    .long 8

    .balign 8
framebuffer_tag_start:  
    .word 0x0005
    .word 0x0001
    .long 20
    .long 1024
    .long 768
    .long 32
framebuffer_tag_end:    
    #required end tag
    
    .balign 8
    .word 0     # type
    .word 0     # flags 
    .long 8     # size

header_end:

address_tag_start:      
        .short 0x0002
        .short 1
        .long address_tag_end - address_tag_start
        /*  header_addr */
        .long   header_start
        /*  load_addr */
        .long   _text_start
        /*  load_end_addr */
        .long   _data_end
        /*  bss_end_addr */
        .long   _bss_end
address_tag_end:

entry_address_tag_start:        
        .short 0x0003
        .short 0x0001
        .long entry_address_tag_end - entry_address_tag_start
        /*  entry_addr */
        .long kernel_start
entry_address_tag_end: