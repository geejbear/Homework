#include <stdint.h> // specific length types (uint32_t)

// RGBA layout in 32 bits (aka 4 bytes)
// RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA

int main()
{
    uint32_t color; // assume this already has a value and we don't know it
    
    // find the alpha component of color:
    
    // clear the first three bytes and keep the last byte as is
    uint32_t alpha = color & 0x000000FF;
    
    // clear everything but the bits that hold the blue color component
    uint32_t blue = color & 0x0000FF00;
    blue >>= 8;
    // or combined into one step:
    // uint32_t blue = (color & 0x0000FF00) << 8;

    // TODO: get green and red components (do this in assignment.c)
    
    
    // TODO: summarize the above bit operation:
    // 1. what you need to know about the integer to do bit ops on it
    // 2. steps to do the bit ops
    
    // =========================================================================
    // =========================================================================
    // CONSOLE CELL INFORMATION (2 bytes)
    // b: background color
    // f: foreground color
    // c: character (ASCII value)
    
    // INTEGER LAYOUT
    // bbbbffff cccccccc
    
    uint16_t console_cells[2000]; // assume screen has contents
    
    // find what character is displayed in console cell (15, 27)
    // after a calculation, we find that coord (15, 17) is at index 350.
    
    // steps
    // 1. clear bits you don't need (& the number with a bit mask)
    // 2. make sure the bits you want are in the right place
    
    uint16_t character = console_cells[350] & 0x00FF;
    
    uint16_t color = (console_cells[350] & 0xFF00) >> 8;
    
    uint16_t fg_color = (console_cells[350] & 0x0F00) >> 8;
    
    uint16_t bg_color = (console_cells[350] & 0xF000) >> 12;
    
    return 0;
}
