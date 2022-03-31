
#include <riscv.h>
#include <types.h>
#include <timer.h>
#include <lib.h>

#define MTVEC_VECTORED_MODE 0x1U

uint64 *mtime = (uint64 *)0x0200BFF8;

uint64 r_mtime();

extern void trap_vector(), trap_vectors();

extern long long _bss_start[];
extern long long _bss_end[];
extern uint8 sp_top[];
uint8 interrupt_stack[4096];    

extern void switch_context(void);

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
    uart_init();
    uint64 hardid = r_mhartid();
    uint64 mtime_start;

    clear_bss();
    hex2str((uint64)trap_vectors + MTVEC_VECTORED_MODE, times);
    w_mtvec((uint64)trap_vectors + MTVEC_VECTORED_MODE);
    timer_init();
    enable_timer();
    uint64 index = 0;
    while(1){
        *(sp_top + index) = '1';
        index += 1024;
        hex2str((sp_top + index), times);
        //puts(times);
        //putc('\n');
        if(*(sp_top + index) != '1'){
            //while(1);
        }
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


void trap_handler(uint64 mepc, uint64 mcause)
{
    char buf[256];
    hex2str(mepc, buf);
    puts(buf);
    putc('\n');
    puts("mcause : ");
    hex2str(mcause & 0xff, buf);
    puts(buf);
    putc('\n');
    if((mcause & 0xff) ^ 0x07 == 0) {
        puts("timer interrupt");
        set_timer();
    }
}