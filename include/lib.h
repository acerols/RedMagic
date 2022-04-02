#include <types.h>

#define NULL ((void *)0)

int putc(unsigned char c);
int puts(unsigned char *s);
int getc(void);
void dec2str(uint64 dec, char *str);
void bin2str(uint64 bin, char *str);
void hex2strd(uint64 hex, char *str, int digit);
void hex2str(uint64 hex, char *str);
void memset(void *dest, uint64 val, uint64 size);
void *malloc(uint64 size);