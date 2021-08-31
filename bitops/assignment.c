#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if 0 // TEMP
typedef struct
{
    // 4. Write a struct that stores r, g, b, a
    // values in individual members.
    // Check your answer with Tom before moving on.
} Color;
#endif


#if 0 // TEMP
void PrintColor32(uint32_t color32)
{
    // 6. additional practice: complete this function
    
    printf("0x%08X (%d, %d, %d, %d)\n", ?);
}
#endif


#if 0 // TEMP
Color ColorFrom32(uint32_t color)
{
    Color result;
    
    // 5. complete this function, which converts a 32-bit color value
    // to a Color struct.
    
    return color;
}
#endif


int main()
{
    srand((unsigned)time(NULL));
    
    uint32_t color = rand();
    printf("random RGBA color: 0x%08X\n", color); // to check 1. and 3.
    
    // 1. find the green component:
    uint8_t green = 0;
    
    // 2. non-related knowledge: what does the specificer %02X do?
    printf("green component: 0x%02X (%d)\n", green, green);
    
    // 3. find the red component:
    uint8_t red = 0;
    
    printf("red component: 0x%02X (%d)\n", red, red);
    
    return 0;
}
