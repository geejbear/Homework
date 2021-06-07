/* hunt.c
 * -----
 * Author : Geejbear
 * Created : May 29, 2021
 * Revision: T. Foster
 * Description : game
 *
 * TODO LIST
 * - X keep the player from going off screen
 * - _ try somthing simple like place an item(s) the player collects
 * - _ 
 */
#include <dos.h>
#include <conio.h>
#include <stdbool.h> 

#define JEWEL 4
#define SMILY 2
// TYPES, STRUCTS, ENUMS
enum state
{
    STATE_EMERALD,
    STATE_RUBY,
    STATE_DIAMOND,
}; 
// DATA

// global variables are initialized to 0 by default
int player_x = 10;
int player_y = 10;

// FUNCTIONS

int river(int n)
{
    int fib[n];
    fib[0] = 1;
    fib[1] = 1;
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        cprintf("%d\n", fib[i]);
    }
    return 0;
}
void collect(int x, int y, int COLOR)
{
    gotoxy(x, y);
    putch(SMILY);
    textcolor(COLOR); 
}

void sound_collect()
{
    sound(220, 115);
    //sound(247, 115);
    sound(554, 115);
    sound(329, 115);
    //sound(440, 115);
}
void jewel(int x, int y, int COLOR)
{
    gotoxy(x, y);
    textcolor(COLOR);
    putch(JEWEL);
    textcolor(LIGHTGRAY);
}


void key_hit() // this function: every time a hit is hit
{
    clrscr();
    int key = getch();

    switch (key) {
        case 'w':
            --player_y;
            if (player_y < 1) {
                ++player_y;
            }
            break;
        case 's':
            ++player_y;
            if (player_y > 20) {
                --player_y;
            }    
            break;
        case 'a':
            --player_x;
            if (player_x < 1) {
                ++player_x;
            }
            break;
        case 'd':
            ++player_x;
            if (player_x > 20) {
                --player_x;
            }
            break;
        default:
            break;
    }

    //cprintf("%d %d", player_x, player_y);
    gotoxy(player_x, player_y);
    putch(SMILY);
}

int main()
{
    textmode(C40);
    setscreensize(20, 20);
    setcursor(0);
    initdos();
    
    gotoxy(player_x, player_y);
    putch(SMILY);

    int emerald_count = 0;
    int ruby_count = 0;
    int diamond_count = 0;
    
    // study this:
    // var = var - 1;
    // var -= 1;
    // var--;
    
    // game loop
    while (1) {
        
        jewel(1, 4, GREEN);
        jewel(3, 10, RED);
        jewel(4, 16, LIGHTCYAN);

        gotoxy(1, 1);
        textcolor(LIGHTBLUE);
        river(23);

      
        gotoxy(5, 1);
        textcolor(GREEN);
        cprintf("%c=%d ", JEWEL, emerald_count);
        textcolor(RED);
        cprintf("%c=%d ", JEWEL, ruby_count);
        textcolor(LIGHTCYAN);
        cprintf("%c=%d", JEWEL, diamond_count);
        textcolor(LIGHTGRAY);

        
        int state = STATE_EMERALD;
        
        switch (state) {
        
            case STATE_EMERALD:
                if (player_x == 1 && player_y == 4) { 
                    collect(1, 4, GREEN);
                    emerald_count++;
                    cprintf("%c=%d", JEWEL, emerald_count);
                    sound_collect();
                    textcolor(LIGHTGRAY);
                    refresh();
                    break;
                }    
            case STATE_RUBY:
                if (player_x == 3 && player_y == 10) {
                    collect(3, 10, RED);
                    ruby_count++;
                    cprintf("%c=%d", JEWEL,ruby_count);
                    sound_collect();
                    textcolor(LIGHTGRAY);
                    break;
                }
            case STATE_DIAMOND:
                if (player_x == 4 && player_y == 16) {
                    collect(4, 16, LIGHTCYAN);
                    diamond_count++;
                    cprintf("%c=%d", JEWEL, diamond_count);
                    sound_collect();
                    textcolor(LIGHTGRAY);
                    break;
                }
            default:
                break;
        }
        // add code to check for a key press (kbhit & getch)
        if (kbhit()) {
            key_hit();
            
        }
        
        refresh();
    }
    return 0;
}
