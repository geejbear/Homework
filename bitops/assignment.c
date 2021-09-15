#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if 1 // TEMP
typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} Color;
#endif

Color ColorFrom32(uint32_t color)
{
    Color result;
	
	uint32_t mask = 0xFF000000;
    result.red = (color & mask) >> 24;

	mask = 0x00FF0000;
	result.green = (color & mask) >> 16;

	mask = 0x0000FF00;
    result.blue = (color & mask) >> 8;
	
	mask = 0x000000FF;
    result.alpha = color & mask;
        
    return result;
}


#if 1 // TEMP
void PrintColor32(uint32_t color32)
{
	Color clr = ColorFrom32(color32);

    // 6. additional practice: complete this function
    printf("0x%08X (%d, %d, %d, %d)\n", color32, clr.red, clr.green, clr.blue, clr.alpha);
}
#endif


int main()
{
    uint32_t color = 0x65FB8C85;
    
	printf("Color: 0x%08X\n", color);
    
	// random generated number: 
	// 0x65FB8C85
	// 01100101 11111011 100001100 100000101
	
	//green:
	//     01100101 11111011 100001100 100000101
	//   & 00000000 11111111 000000000 000000000
	//  ======================================
	//     00000000 11111011 000000000 00000000
    //>>16 00000000 00000000 000000000 11111011
	//red
	//  01100101 11111011 100001100 100000101
	//& 11111111 00000000 000000000 000000000
	//  ======================================
	//  01100101 00000000 000000000 000000000

// 1. find the green component:

	uint32_t mask = 0x00FF0000;
    uint8_t green = (color & mask) >> 16;
    
    // 2. non-related knowledge: what does the specificer %02X do?
	//A: It prints the hexadecimal and diplays it in two digits.
    printf("green component: 0x%02X (%d)\n", green, green);

    // 3. find the red component:
	mask = 0xFF000000;
    uint8_t red = (color & mask) >> 24;
    
    printf("red component: 0x%02X (%d)\n", red, red);


    return 0;
}
