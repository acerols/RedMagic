
#include <riscv.h>
#include <types.h>
#include <timer.h>
#include <lib.h>
#include <thread.h>

#define MTVEC_VECTORED_MODE 0x1U

uint64 *mtime = (uint64 *)0x0200BFF8;

uint64 r_mtime();

extern void trap_vector(), trap_vectors();

extern long long _bss_start[];
extern long long _bss_end[];
extern uint8 sp_top[];
uint8 interrupt_stack[4096];    

struct ret_reg{
    uint64 sp;
    uint64 ra;  
}rr;

extern void switch_context(void *, void *);

uint64 console_buf[256];

void clear_bss() {
    memset(_bss_start, 0, _bss_end - _bss_start);
}

void init()
{
    clear_bss();
    uart_init();
    //hex2str((uint64)trap_vectors + MTVEC_VECTORED_MODE, times);
    //w_mtvec((uint64)trap_vectors + MTVEC_VECTORED_MODE);
    //timer_init();
    //enable_timer();     
}

uint64 task_count = 0;
thread task_stack[10];
uint64 now_task_id = 0;

void initTask(void (*func)())
{
    task_stack[task_count].context_ptr = (context *)&task_stack[task_count].stack[0x1000] - 1;
    task_stack[task_count].context_ptr->ra = (uint64)func;
    task_stack[task_count].sp = (uint8 *)task_stack[task_count].context_ptr;
    
    puts("sp top addr :");
    hex2str((uint64)task_stack[task_count].stack, console_buf);
    puts(console_buf);
    puts("\n");
    puts("sp bottom addr :");
    hex2str((uint64)task_stack[task_count].context_ptr, console_buf);
    puts(console_buf);
    puts("\n");
    puts("sp addr : ");
    hex2str((uint64)task_stack[task_count].sp, console_buf);
    puts(console_buf);
    puts("\n");

    task_count++;

}

void taskSwitch(thread *from, thread *to)
{
    switch_context(&to->sp, &from->sp);
}

void dump_register(uint64 id);

void schedule(void)
{
    uint64 from = now_task_id;
    uint64 to = (now_task_id + 1) % task_count;
    now_task_id = to;
    puts("\n----------------scheduling----------------\n");
    puts("from : ");
    hex2str(from, console_buf);
    puts(console_buf);
    puts("\n");
    puts("to : ");
    hex2str(to, console_buf);
    puts(console_buf);
    puts("\n");

    // print task_stack[from].sp
    puts("from sp : ");
    hex2str((uint64)task_stack[from].sp, console_buf);
    puts(console_buf);
    puts("\n");

    // print task_stack[to].sp
    puts("to sp : ");
    hex2str((uint64)task_stack[to].sp, console_buf);
    puts(console_buf);
    puts("\n");

    // dump context of from
    puts("from context : ");
    dump_register(from);
    puts("\n");

    // dump context of to
    puts("to context : ");
    dump_register(to);
    puts("\n");

    puts("\n----------------switch----------------\n");

    taskSwitch(&task_stack[from], &task_stack[to]);
}

void task1()
{
    while(1){
        puts("task1");
        for(int i = 0; i < 1000000; i++);
        schedule();
    }
}

void task2()
{
    while(1){
        puts("task2");
        for(int i = 0; i < 1000000; i++);
        schedule();
    }
}

void dump_register(uint64 id)
{
    uint64 *p = task_stack[id].sp;
    for(int i = 0; i < (sizeof(context)/sizeof(uint64)); i++){
        if (p[i] == 0) {
            puts("00000000");
        } else {
            hex2str(p[i], console_buf);
            puts(console_buf);
        }
        puts("\n");
    }
}

void main()
{
    init();
    initTask(task1);
    initTask(task2);
    load_context(&task_stack[0].sp);
    while(1){
        puts("Hello,World!\n");
        for(uint64 i = 0; i < 100000000; i++);
    }
}

void not_main()
{
    puts("not_main");
    while(1);
}

void trap_handler(uint64 sp, uint64 mcause, uint64 mepc)
{
    puts("trap_handler");
    while(1);
}