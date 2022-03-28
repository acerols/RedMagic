#include <riscv.h>
#include <types.h>
#include <timer.h>

#include <uart.h>

uint64 interval = 10000000;
void timer_init()
{
    uint64 mstatus = r_mstatus();
    mstatus |= MSTATUS_MIE;
    w_mstatus(mstatus);

}

uint64 *CLINT_MTIMECMP = (uint64 *)0x02004000;
uint64 *CLINT_MTIME = (uint64 *)0x0200BFF8;
void enable_timer()
{
    int id = r_mhartid();
    
    *(uint64 *)(CLINT_MTIMECMP) = *(uint64 *)(CLINT_MTIME) + interval;

    uint64 mie = r_mie();
    mie |= MIE_MTIE;
    w_mie(mie);
}

void set_timer()
{
    *(uint64 *)(CLINT_MTIMECMP) = *(uint64 *)(CLINT_MTIME) + interval;
}