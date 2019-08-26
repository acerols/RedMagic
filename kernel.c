#include <multiboot2.h>
#include <kstdlib.h>
#include <memory.h>
#include <section.h>

void _kernel_entry(unsigned long magic, unsigned long addr)
{
    struct multiboot_tag *tag;
    unsigned size;

    initBSS();

    //for(;;);

    return;
}