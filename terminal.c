#include <vga.h>
#include <terminal.h>

void termianl_initialize(void)
{
    size_t x, y;

    t_row = 0;
    t_column = 0;
    t_color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    t_buffer = (uint16_t *)0xB8000;
    for(y = 0; y < VGA_HEIGHT; ++y){
        for(x = 0; x < VGA_WIDTH; ++x){
            const size_t index = y * VGA_WIDTH + x;
            t_buffer[index] = vga_entry(' ', t_color);
        }
    }
    terminal_writestring("Initialize Terminal... OK\n");

}

void terminal_setcolor(uint8_t color)
{
    t_color = color;
}

void terminal_putentryat(uint8_t c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    t_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(uint8_t c)
{
    if(c == '\n'){
        ++t_row;
        t_column = 0;
        return;
    }

    terminal_putentryat(c, t_color, t_column, t_row);
    if(++t_column == VGA_WIDTH){
        t_column = 0;
        if(++t_row == VGA_HEIGHT)t_row = 0;
    }
}

void terminal_write(const uint8_t *data, size_t size)
{
    for(size_t i = 0; i < size; i++){
        terminal_putchar(data[i]);
    }
}

static size_t strlen(const uint8_t *str)
{
    size_t len = 0;
    while(str[len])++len;
    return len;
}

void terminal_writestring(const uint8_t *data)
{
    terminal_write(data, strlen(data));
}