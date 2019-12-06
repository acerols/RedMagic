/*
#include <multiboot2.h>
#include <kstdlib.h>
#include <memory.h>
#include <io.h>
*/
extern void errors(void);
extern void mem_in16(unsigned short *, unsigned short d);

typedef unsigned long long size_t;

typedef struct _font{
  unsigned char color;
  unsigned char c;
}FONT;

void write_string(const char *data, size_t size)
{
    size_t i;
    unsigned short *screen;
    screen = (unsigned short *)0xb8000;
    for(i = 0; i < size; ++i){
        *screen++ = ((0x0f) << 8) | data[i];
    }
}

void _kernel_entry(unsigned long magic, void *addr)
{
    //struct multiboot_tag *tag;

        //errors();
    write_string("AAAA", 4);
    while(1);

    for(;;);

    return;
}

