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
#define MILLISECONDS 100 // fine, or maybe 'NOTE_LEN_MS'
#define CH_BEER 0x96
#define CH_WINE 0x59
#define CH_SMILY 0x02
#define TEXT_MARGIN 8

#define TEXT_MARGIN 8

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

// name: something like print_icon (functions begin with a verb/action word)
// remove redundant params: arrows (these are constants)
void print_icon(int color_icon, char ch_icon)
            // -> Y <- , -> B <-
{
    textcolor(color_icon);
    gotoxy(TEXT_MARGIN, wherey());
    putch(CH_ARROW_R);
    putch(ch_icon);
    putch(CH_ARROW_L);
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
    gotoxy(TEXT_MARGIN, wherey());
    cprintf("'ello Gov'nor!\n\n");
    gotoxy(TEXT_MARGIN, wherey());
    cprintf("wha'can i getcha?\n");   
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
    print_icon(RED, CH_WINE);
    cprintf("\n\n");
    textcolor(LIGHTGRAY);
    cprintf("or beer...? press 'B'\n\n\n");
    print_icon(YELLOW, CH_BEER);
    
}

// TODO: make these one function (DRY)
// remove arrow params
void choice(int color_icon, char ch_icon, 
             int color_text)
{
    sleep(1);
    sound_major();
    clrscr();
    print_icon(color_icon, ch_icon);
    cprintf("\n\n\n");
    textcolor(color_text);
    cprintf("press '3'...");
    putch(CH_ARROW_R);
}

void end()
{
    textcolor(LIGHTMAGENTA);
    gotoxy(18, 6);
    putch(0x02);
    cprintf("\n\n");
    gotoxy(TEXT_MARGIN, wherey());
    cprintf("'ier ya go, mate!\n\n");    
    gotoxy(TEXT_MARGIN, wherey());
    cprintf("on d'house!\n"); 
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
                        choice(RED, CH_WINE, 
                                LIGHTGRAY);
                        state = STATE_END;
                   
                    } else if (key == 'b') {
                        choice(YELLOW, CH_BEER, 
                                LIGHTGRAY);
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
