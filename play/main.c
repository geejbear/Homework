#include "play.h"
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <math.h>

int main()
{
    int tempo;
    printf("How many beats per minute?: ");
    scanf("%d", &tempo);

    printf("\nC(1)\tC#(2)\tD(3)\tD#(4)\n");
    printf("E(5)\tF(6)\tF#(7)\tG(8)\t\n");
    printf("G#(9)\tA(10)\tB♭(11)\tB(12)\t\n");
    
    printf("\nChoose a note and print its number :");
    int input;
    scanf("%d", &input);    

    printf("\n1\t2\t3\t4\t5\t6\t7\n");
    printf("Choose an octave: ");
    int oct;
    scanf("%d", &oct);
    
    int num;
    printf("\nPrint a note value from the following options :\n");
    printf("\n1\t2\t4\t8\t16\n");
    
    printf("\n");
    
    scanf("%d", &num);
    
    float frequency = freq(input - 1, oct);
    float ms = notevalue_to_ms(num, tempo);
    
    printf("\nFrequency: %.4f Hz\n", frequency);
    printf("Milliseconds: %.2f\n\n", ms);
    
    // last step in Libdos:
    initdos();
    textmode(C40);
    sound(frequency, ms);
    gotoxy(1, 1);
    textcolor(YELLOW);
    cprintf("\nFrequency: %.4f Hz\n", frequency);
    textcolor(GREEN);
    cprintf("Milliseconds: %.2f\n\n", ms);
    
    return 0;
}

#if 0
int main()
{
    int value;
    scanf("%d", &value);
    value = clamp(value, 1, 7);
    printf("%d", value);
    return 0;
}
#endif