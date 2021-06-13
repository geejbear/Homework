/* hunt.c
 * -----
 * Author : Geejbear
 * Created : May 29, 2021
 * Revision: T. Foster
 * Description : game
 *
 * TODO LIST
 * X keep the player from going off screen
 * - try somthing simple like place an item(s) the player collects
 * - use play() from play module
 * - write ascii.h with enum for 1-31 ascii glyph
 * - write a function clmp
 * - simplify: one gem -> collect it
 * - - random location
 *
 */
// =============================================================================
// INCLUDES
#include <dos.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "play.h"
// =============================================================================
// DEFINES
#define MAX_SCREEN_SIZE 20
#define MIN_SCREEN_SIZE 20
// =============================================================================
// TYPES / ENUMS
enum ascii
{
    CH_VOID,
    CH_SMILY1,
    CH_SMILY2,
    CH_HEART,
    CH_DIAMOND,
    CH_CLOVE,
    CH_SPADE,
    CH_SMALL_CIRCLE1,
    CH_SMALL_CIRCLE2,
    CH_BIG_CIRCLE1,
    CH_BIG_CIRCLE2,
    CH_MALE,
    CH_FEMALE,
    CH_QUAVER,
    CH_SEMIQUAVERS,
    CH_SPARKLE,
    CH_NATURAL = 21,
    CH_BLOCK,
    CH_ARROW_UP = 24,
    CH_ARROW_DOWN,
    CH_ARROW_LEFT,
    CH_ARROW_RIGHT,
    CH_SHARP = 35,
    CH_FLAT = 98,
};

// =============================================================================
// DATA
enum 
{
    STATE_SEARCH,
    STATE_FIND,
    STATE_COLLECT,
};

// =============================================================================
// PROTOTYPES (function declarations)

/*state = STATE_FIND;
switch (state) {
    case 'w':
}*/

// =============================================================================
// PRIVATE FUNCTIONS (private aka static functions)
// =============================================================================
// PUBLIC FUNCTIONS (non-static functions, aka ones that go in the header file)
// TODO: better CHAR_print_item

// TYPES, STRUCTS, ENUMS

// DATA (state)

// global variables are initialized to 0 by default
int player_x = 10;
int player_y = 10;

int state;

// FUNCTIONS

int clmp(int value, int min, int max)
{
    if (value < min) {
        value = min;
        return value;
    }

    if (value > max) {
        value = max;
        return value;
    } else if (value >= min || value <= max) {
        return value;
    }
    return 0;
}

int print_river(int n)
{
    clmp(n, 30, 1);

    int *fib = malloc( n * sizeof(int) );
    fib[0] = 1;
    fib[1] = 1;

    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        cprintf("%d\n", fib[i]);
    }

    free(fib);

    return 0;
}

void sound_collect()
{
play(1, 4, 120, 60);
play(5, 4, 120, 60);
play(8, 4, 120, 60);
}

void collect(int x, int y)
{
        
    if ((player_x == x + 1 && player_y == y) ||
                (player_x == x && player_y == y + 1) ||
                (player_x == x - 1 && player_y == y) ||
                (player_x == x && player_y == y - 1)) {
        textcolor(WHITE);
        gotoxy(4, 4);
        putch(CH_DIAMOND);
        sound_collect();
    } else if (player_x == x && player_y == y) {
        textcolor(LIGHTGRAY);
        gotoxy(x, y);
        putch(CH_SMILY1);
        clrscr();
    }   
}

void print_item(int x, int y, int COLOR, char ICON)
{
    gotoxy(x, y);
    textcolor(COLOR);
    putch(ICON);
    textcolor(LIGHTGRAY);
}

void first_level()
{
    cprintf("%d %d", player_x, player_y);
    
    gotoxy(player_x, player_y);
    putch(CH_SMILY1);
    print_item(4, 4, GREEN, CH_DIAMOND);

    collect(4, 4);
}


void key_hit() // this function: every time a hit is hit
{
    clrscr();
    int key = getch();
    
    //state = STATE_SEARCH;
    
    switch (key) {
        case 'w': // TODO: optimize logic for wasd
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

    // TODO: the player has moved, does something happen?
    first_level();
    
}

int main()
{
    textmode(C40);
    setscreensize(MAX_SCREEN_SIZE, MIN_SCREEN_SIZE);
    setcursor(0);
    initdos(); 
    gotoxy(player_x, player_y);
    putch(CH_SMILY1);

    while (1) {

        // add code to check for a key press (kbhit & getch)
        if (kbhit()) {
            key_hit();
        }

            refresh();
    }    
        return 0;
}
