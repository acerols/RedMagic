#include <memory.h>
#include <kstdlib.h>

void initBSS(void)
{
    kmemset((void *)&_bss_start, 0x00, ((unsigned int)&_bss_end - (unsigned int)&_bss_start));
}

