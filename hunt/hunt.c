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
#include "utility.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


// =============================================================================
// DEFINES

#define SCREEN_W    20
#define SCREEN_H    20

// note: minimum x and y is 1
#define MAX_X       SCREEN_W
#define MAX_Y       SCREEN_H

#define MIN_X       1
#define MIN_Y       1

#define OCTAVE      4  
#define NOTE_VALUE  16  
#define TEMPO       220   
#define STARTING_PT 10 


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
    CH_NAK = 21,
    CH_BLOCK,
    CH_ARROW_UP = 24,
    CH_ARROW_DOWN,
    CH_ARROW_LEFT,
    CH_ARROW_RIGHT,
    CH_POUND = 35,
    CH_LETTER_B = 98,
    // TODO: look at ascii chart and add other potentially useful characters
};

// =============================================================================
// PROTOTYPES (function declarations)


// =============================================================================
// DATA (state) global variables are initialized to 0 by default

bool gem_collected = false; // this is a possibility


// TODO: DRY: single struct to represent game objects
typedef struct
{
    int player_x; // remove reduncant 'player' part of name
    int player_y;
} player_t;

typedef struct
{
    int gem_x; // TODO: in code, stop using "magic value" (4, 4)
    int gem_y;
} gem_t;
// TODO: gem location data

// =============================================================================
// FUNCTIONS

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
    play(NOTE_C, OCTAVE, NOTE_VALUE, TEMPO); 
    play(NOTE_E, OCTAVE, NOTE_VALUE, TEMPO);
    play(NOTE_G, OCTAVE, NOTE_VALUE, TEMPO);
}

// TODO: fix param names: capitals are for #defined constants etc: used lowercase
// TODO: function name: all lowers
void CHAR_print_item(gem_t *g, int COLOR, char ICON)
{
    g->gem_x = 10;
    g->gem_y = 10;
    gotoxy(g->gem_x, g->gem_y);
    textcolor(COLOR);
    putch(ICON);
    textcolor(LIGHTGRAY);
}

// TODO: function should do only one thing: draw (no game changes, for instance)
void draw_everything(player_t *p, gem_t *gem)
{
    
    gotoxy(20, 1); // TEMP: it helps me visualize x and y
    cprintf("X");
    gotoxy(1, 20);
    cprintf("Y");
        
    //p->player_x = rand() % MAX_X;
    //p->player_y = rand() % MAX_Y;
    gotoxy(p->player_x, p->player_y);
    putch(CH_SMILY1);
    
    //gotoxy(1, 1); // DEBUG: player location
    printf("%d %d\n", p->player_x, p->player_y);
    
    gotoxy(gem->gem_x, gem->gem_y);
    textcolor(LIGHTGREEN);
    putch(4); // TODO: use constant
}

/*void print_rand_ITEM()
{
    int ctime = time(NULL);
    srand(ctime);

    gem_x = rand() % MAX_X;
    gem_y = rand() % MAX_Y;    
   
    CHAR_print_item(*ptr1, *ptr2, GREEN, CH_DIAMOND);
}
*/
/*void collect_gem()
{
    if ( !gem_collected && player_x == *ptr1 && player_y == *ptr2 ) { // player is on gem!
        // do collect gem stuff
        gem_collected = true;
        sound_collect();
    }
}*/

void key_hit(player_t *p, gem_t *gem) // this function: every time a hit is hit
{
    
    clrscr();
    int key = getch();
    
    switch (key) {
        case 'w': // TODO: optimize logic for wasd
            --p->player_y;
            if (p->player_y < MIN_Y) { // TODO: this is a good use case for clamp()
                p->player_y = MIN_Y;
            }
            break;
        case 's':
            ++p->player_y;
            if (p->player_y > MAX_Y) { 
                p->player_y = MAX_Y;
            }
            break;
        case 'a':
            --p->player_x;
            if (p->player_x < MIN_X) {
                p->player_x = MIN_X;
            }
            break;
        case 'd':
            ++p->player_x;
            if (p->player_x > MAX_X) {
                p->player_x = MAX_X;
            }
            break;
        default:
            break;
    }
    // TODO: the player has moved, does something happen?
    //player_t plr;
    draw_everything(p, gem); // TODO: this is good, keep it
    //collect_gem();
}

int main()
{
    textmode(C40);
    setcursor(0);
    setscreensize(SCREEN_W, SCREEN_H);
    initdos();
    
    srand((unsigned)time(NULL));
    
    player_t plr;
    plr.player_x = (rand() % 10) + 1;
    plr.player_y = (rand() % 10) + 1;
    gem_t gem;
    gem.gem_x = (rand() % 20) + 1;
    gem.gem_y = (rand() % 20) + 1;
    
    draw_everything(&plr, &gem);
    //print_rand_ITEM();
    
    while (1) {
        if (kbhit()) {
            player_t plr;
            key_hit(&plr, &gem);
            

        }
        refresh();
    }    
    
    return 0;
}
