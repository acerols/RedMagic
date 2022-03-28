#include <types.h>

int putc(unsigned char c);
int puts(unsigned char *s);
int getc(void);
void dec2str(uint64 dec, char *str);
void bin2str(uint64 bin, char *str);
void hex2str(uint64 hex, char *str);