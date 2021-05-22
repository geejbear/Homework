/*
 * Author: Geejbear
 * Date 22.05.2021
 * Revised by: Thomas Foster
 * Created with the LibTC Turbo C library (https://github.com/teefoss/LibTC) 
 * "Bar Game" - a short interactive story implementing Turbo and Modern C
 */

#include <dos.h>
#include <conio.h>
#include <stdbool.h>

#define CH_ARROW_R 0x1A 
#define CH_ARROW_L 0x1B
#define MILLISECONDS 100
#define CH_BEER 0x96
#define CH_WINE 0x59
#define CH_SMILY 0x02


void sound_major()
{
    sound(261, MILLISECONDS);
    sound(326, MILLISECONDS);
    sound(391, MILLISECONDS);
}

void sound_quit()
{
    sound(391, MILLISECONDS);
    sound(326, MILLISECONDS);
    sound(261, MILLISECONDS);
}

void icon(int color_icon, char ch_arrow_r, 
            char ch_icon, char ch_arrow_l) 
            // -> Y <- , -> B <-
{
    textcolor(color_icon);
    cprintf("       ");
    putch(ch_arrow_r);
    putch(ch_icon);
    putch(ch_arrow_l);
}

void intro()
{
    textcolor(LIGHTGRAY);
    cprintf("Press '1' to start "); 
    putch(CH_ARROW_R);
    textcolor(LIGHTMAGENTA);
    gotoxy(18, 6);
    putch(CH_SMILY); 
}

void order_drink()
{
    cprintf("\n\n");
    cprintf("        'ello Gov'nor!\n\n");
    cprintf("        wha'can i getcha?\n");   
    textcolor(LIGHTGRAY);
    cprintf("\n\n\n\n");
    cprintf("Press '2' to order ");
    putch(CH_ARROW_R); 
}

void choice_drink()
{
    clrscr();
    textcolor(LIGHTGRAY);
    cprintf("wine? press 'W'\n\n\n");
    
    icon(RED, CH_ARROW_R, CH_WINE, CH_ARROW_L);
    cprintf("\n\n");
    textcolor(LIGHTGRAY);
    cprintf("or beer...? press 'B'\n\n\n");
    
    icon(YELLOW, CH_ARROW_R, CH_BEER, CH_ARROW_L);
    
}

// TODO: make these one function (DRY)
void choice(int color_icon, char ch_arrow_r, char ch_icon, 
            char ch_arrow_l, int color_text, char ch_arrow_r2)
{
    sleep(1);
    sound_major();
    clrscr();
    icon(color_icon, ch_arrow_r, ch_icon, ch_arrow_l);
    cprintf("\n\n\n");
    textcolor(color_text);
    cprintf("press '3'...");
    putch(ch_arrow_r2);
}

void end()
{
    textcolor(LIGHTMAGENTA);
    gotoxy(18, 6);
    putch(0x02);
    cprintf("\n\n");
    cprintf("        'ier ya go, mate!\n\n");    
    cprintf("        on d'house!\n"); 
    textcolor(LIGHTGRAY);
    cprintf("\n\n\nthe end! (press 'Q')");
}

enum
{
    STATE_GREETING,     //initializing state "press '1' to start"
    STATE_ORDER,        // "press '2' to order"
    STATE_CHOICES,      // "wine...? or beer...?"
    STATE_WINE_AND_BEER,         
    STATE_END,          //ending scene...
    STATE_QUIT,         //quit libDOS;
};


int main()
{
    setcursor(CURSOR_NONE);
    textmode(C40);
    initdos();
    
    intro();
    int state = STATE_ORDER;
    
    while (1) {
        
        if ( kbhit() ) {
            
            int key = getch();
                        
            switch (state) {
                case STATE_ORDER:
                    if ( key == '1' ) {
                        order_drink();
                        state = STATE_CHOICES;
                    }
                    break;
                case STATE_CHOICES: 
                    if (key == '2') {        
                        choice_drink();
                        state = STATE_WINE_AND_BEER;
                    }    
                    break;
                case STATE_WINE_AND_BEER:
                    if (key == 'w') {
                        choice(RED, CH_ARROW_R, CH_WINE, 
                                CH_ARROW_L, LIGHTGRAY, CH_ARROW_R);
                        state = STATE_END;
                   
                    } else if (key == 'b') {
                        choice(YELLOW, CH_ARROW_R, CH_BEER, 
                                CH_ARROW_L, LIGHTGRAY, CH_ARROW_R);
                        state = STATE_END;
                    }    
                    break;
                case STATE_END:
                    if (key == '3') {
                        end();
                        state = STATE_QUIT;
                    }    
                    break;
                case STATE_QUIT:
                    if (key == 'q') {
                        sound_quit();
                        sleep(1);  
                        return 0;
                    }
                    break; 
            }
        }
        
        refresh();
    }
}
