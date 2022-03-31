#include <types.h>
#include <memlayout.h>
#include <uart.h>

#define RHR 0
#define THR 0
#define IER 1
#define FCR 2
#define LCR 3
#define MCR 4
#define LSR 5

#define Reg(reg) ((volatile unsigned char *)(UART0 + reg))

#define IE_RX_DATA_READY 0x01
#define IE_TX_ENABLE (1 << 1)

#define FCR_FIFO_ENABLE (1 << 0)
#define FCR_FIFO_CLEAR (3 << 1)

#define LCR_EIGHT_BITS (3 << 0)
#define LCR_BAUD_LATCH (1 << 7)

#define LSR_RX_DATA_READY (1 << 0)
#define LSR_TX_IDLE (1 << 5)

#define UART_TX_BUF_SIZE 32
char uart_tx_buf[UART_TX_BUF_SIZE];

uint64 uart_tx_w;
uint64 uart_tx_r;

#define ReadReg(reg) (*(Reg(reg)))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

void uart_init()
{
    WriteReg(IER, 0x00);

    WriteReg(LCR, LCR_BAUD_LATCH);

    WriteReg(0, 0x03);

    WriteReg(1, 0x00);

    WriteReg(LCR, LCR_EIGHT_BITS);

    WriteReg(FCR, FCR_FIFO_ENABLE | FCR_FIFO_CLEAR);

    WriteReg(IER, IE_RX_DATA_READY | IE_TX_ENABLE);

}

void uart_puts(unsigned char *s)
{
    while(*s != 0){
        uart_putc(*s);
        ++s;
    }
}

void uart_putc(unsigned char c)
{
    //WriteReg(THR, (char)c);
    
    while(1){
        uart_start();
        if(uart_tx_w  == uart_tx_r + UART_TX_BUF_SIZE){
            // buffer full
            continue;
        }
        else{
            uart_tx_buf[uart_tx_w % UART_TX_BUF_SIZE] = c;
            uart_tx_w++;
            return;
        }
    }
}

void uart_start()
{
    while(1){
        if(uart_tx_w == uart_tx_r){
            return;
        }

        if((ReadReg(LSR) & LSR_TX_IDLE) == 0){
            return;
        }

        int c = uart_tx_buf[uart_tx_r % UART_TX_BUF_SIZE];
        uart_tx_r++;

        WriteReg(THR, (char)c);
    }
}

int uart_getc(void)
{
    if(ReadReg(LSR) & 0x01){
        return ReadReg(RHR);
    }
    return -1;
}

void uart_intr(void)
{
    while(1){
        int c = uart_getc();
        if(c == -1){
            break;
        }

    }
}