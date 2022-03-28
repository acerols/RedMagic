#include <uart.h>
#include <types.h>
#include <lib.h>

int putc(unsigned char c)
{
    uart_putc(c);
    return 0;
}

int puts(unsigned char *s)
{
    uart_puts(s);
    return 0;
}

int getc(void)
{
    return uart_getc();
}

void dec2str(uint64 dec, char *str)
{
    int index = 0;
    while(dec > 0){
        str[index++] = dec % 10 + '0';
        dec /= 10;
    }
    // reverse str
    for(int i = 0; i < index / 2; i++){
        char tmp = str[i];
        str[i] = str[index - i - 1];
        str[index - i - 1] = tmp;
    }
    str[index] = '\0';
}

void bin2str(uint64 bin, char *str)
{
    int index = 0;
    while(bin > 0){
        str[index++] = bin % 2 + '0';
        bin /= 2;
    }
    // reverse str
    for(int i = 0; i < index / 2; i++){
        char tmp = str[i];
        str[i] = str[index - i - 1];
        str[index - i - 1] = tmp;
    }
    str[index] = '\0';
}

void hex2str(uint64 hex, char *str)
{
    int index = 0;
    while(hex > 0){
        str[index++] = hex % 16;
        if(str[index - 1] < 10){
            str[index - 1] += '0';
        }
        else{
            str[index - 1] += 'a' - 10;
        }
        hex /= 16;
    }
    // reverse str
    for(int i = 0; i < index / 2; i++){
        char tmp = str[i];
        str[i] = str[index - i - 1];
        str[index - i - 1] = tmp;
    }
    str[index] = '\0';
}