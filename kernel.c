
#include <riscv.h>
#include <types.h>
#include <timer.h>
#include <lib.h>

uint64 *mtime = (uint64 *)0x0200BFF8;

uint64 r_mtime();

extern void trap_vector();

extern long long _bss_start[];
extern long long _bss_end[];

extern void switch_context(void);

volatile int value = 'a';

void clear_bss() {
    long long *p;
    for (p = _bss_start; p < _bss_end; p++) {
        *p = 0;
    }
}

void main()
{
    char *msgs = "Hello,World!\n";
    char times[256];
    int index = 0;
    uart_init();
    uint64 hardid = r_mhartid();
    uint64 mtime_start;

    clear_bss();
    w_mtvec(trap_vector);
    timer_init();
    enable_timer();

    putc(value);
    value = value + 1;
    putc(value);

    while(1){
        //continue;
        //witch_context();
        mtime_start = r_mtime();
        int c = getc();
        if(c != -1){
            putc(c);
        }
        //putc('\n');
        for(int sec = 0; sec < 10000; sec++);
    }
    puts(times);
    putc('0' + hardid);
    puts(msgs);
}
/*
uint64 *CLINT_MTIMECMP = (uint64 *)0x02004000;
void timer_init()
{
    int id = r_mhartid();
    char buf[256];
    int interval = 1000000;

    uint64 addr = (uint64)(CLINT_MTIMECMP);
    hex2str(addr, buf);
    uart_puts(buf);
    uart_putc('\n');
    addr = (uint64)(&CLINT_MTIMECMP[1]);
    hex2str(addr, buf);
    uart_puts(buf);
    uart_putc('\n');

}
*/

uint64 r_mtime()
{
    return *mtime;
}


void trap_handler()
{
    set_timer();
    uart_puts("trap_handler\n");
}