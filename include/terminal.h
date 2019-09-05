#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <stdint.h>
#include <stddef.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static size_t t_row;
static size_t t_column;
static uint8_t t_color;
static uint16_t *t_buffer;

void termianl_initialize(void);
void termianl_setcolor(uint8_t);
void terminal_putentryat(uint8_t c, uint8_t color, size_t x, size_t y);
void terminal_putchar(uint8_t c);
void terminal_write(const uint8_t *data, size_t size);
void terminal_writestring(const uint8_t *data);

#endif