        .section .text
        .equ UART_ADDR, 0x10000000

        .global _start

_start:
        la  sp, sp_top
#        la  s0, message     # set a pointer to head of message
        jal main

halt:
        j halt

