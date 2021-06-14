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
 * - write a function clamp
 * TODO: simplify: one gem -> collect it
 * TODO: random location
 * TODO: try 3 gems
 * - use clamp()
 * TODO: item_t struct
 */

#include <dos.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "play.h"

// =============================================================================
// DEFINES

#define SCREEN_W    20
#define SCREEN_H    20

// note: minimum x and y is 1
#define MAX_X       SCREEN_W
#define MAX_Y       SCREEN_H

// =============================================================================
// STRUCTS / TYPES / ENUMS

enum ascii // TODO: put this in ascii.h -> make names generic
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
    // TODO: look at ascii chart and add other potentially useful characters
};

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

// TODO: better CHAR_print_item

// =============================================================================
// DATA (state) global variables are initialized to 0 by default

int player_x = 10;
int player_y = 10;

bool gem_collected = false; // this is a possibility
int gem_x = 4; // TODO: in code, stop using "magic value" (4, 4)
int gem_y = 4;

// TODO: gem location data

// =============================================================================
// FUNCTIONS

// TODO: move to utility module (utility.c and utility.h)
int clamp(int value, int min, int max)
{
    int result;
    
    if (value < min) {
        result = min;
    } else if (value > max) {
        result = max;
    } else { // in range
        result = value;
    }
    
    return result;
}

int print_river(int n)
{
    clamp(n, 30, 1);

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
    play(1, 4, 120, 60); // TODO: use enum value
    play(5, 4, 120, 60);
    play(8, 4, 120, 60);
}

// TODO: param names
void print_item(int x, int y, int COLOR, char ICON)
{
    gotoxy(x, y);
    textcolor(COLOR);
    putch(ICON);
    textcolor(LIGHTGRAY);
}

void draw_entire_level()
{
    cprintf("%d %d", player_x, player_y);
    
    gotoxy(player_x, player_y);
    putch(CH_SMILY1);
    if ( !gem_collected )
        print_item(4, 4, GREEN, CH_DIAMOND);
}


void key_hit() // this function: every time a hit is hit
{
    clrscr();
    int key = getch();
    
    switch (key) {
        case 'w': // TODO: optimize logic for wasd
            --player_y;
            if (player_y < 1) { // TODO: this is a good use case for clamp()
                ++player_y;
            }
            break;
        case 's':
            ++player_y;
            if (player_y > 20) { // TODO: use #define name
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
    
    // player has moved, but level has not been redrawn
    
    if ( !gem_collected && player_x == 4 && player_y == 4 ) { // player is on gem!
        // do collect gem stuff
        gem_collected = true;
        
        sound_collect();
    }
    
    // TODO: the player has moved, does something happen?
    draw_entire_level();
}

int main()
{
    textmode(C40);
    setscreensize(SCREEN_W, SCREEN_H);
    setcursor(0);
    initdos();
    
    draw_entire_level();

    // TODO: fix your funky indentation!
    while (1) {

        // add code to check for a key press (kbhit & getch)
        if (kbhit()) {
            key_hit();
        }

            refresh();
    }    
        return 0;
}
