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

    printf("\nNOTE_C\tNOTE_C_SHARP\tNOTE_D\tNOTE_D_SHARP\n");
    printf("NOTE_E\tNOTE_F\tNOTE_F_SHARP\tNOTE_G\t\n");
    printf("NOTE_G_SHARP\tNOTE_A\tNOTE_B_FLAT\tNOTE_B\t\n");
    
    printf("\nType your choice of note :");
    char input[20]; //both variables should be th same type 
    char *ptr; 
    ptr = input;
    scanf("%s", &input[0]);    

    printf("\n1\t2\t3\t4\t5\t6\t7\n");
    printf("Choose an octave: ");
    int oct;
    scanf("%d", &oct);
    
    int num;
    printf("\nPrint a note value from the following options :\n");
    printf("\n1\t2\t4\t8\t16\n");
    
    printf("\n");
    
    scanf("%d", &num);
    
    float frequency = freq(ptr, oct);
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