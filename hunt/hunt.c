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

#define MIN_X           1
#define MIN_Y           1
#define MAX_NUM_ITEMS   3

#define OCTAVE      4  
#define NOTE_VALUE  16  
#define TEMPO       220 

#define OBJ_1       'G' 
#define OBJ_2       'C' 
#define OBJ_3       'F' 




// =============================================================================
// STRUCTS / TYPES / ENUMS

enum ascii { // TODO: put this in ascii.h -> make names generic
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

bool item_collected = false; // this is a possibility

typedef struct {
    int x; 
    int y;
}   player_t, entities_t;


// =============================================================================
// FUNCTIONS
void print_objective()
{
    gotoxy(MIN_X, MIN_Y);
    textcolor(YELLOW);
    cprintf("G%c", CH_ARROW_UP);
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

    play(NOTE_G, OCTAVE, NOTE_VALUE, TEMPO);
    play(NOTE_G_SHARP, OCTAVE, NOTE_VALUE, TEMPO);
    play(NOTE_G, OCTAVE, NOTE_VALUE, TEMPO);
    play(NOTE_G_SHARP, OCTAVE, NOTE_VALUE, TEMPO);

}

// TODO: function should do only one thing: draw (no game changes, for instance)
void draw_level(player_t *player, entities_t *flat, entities_t *sharp, entities_t *natural)
{
    print_objective();
    
    gotoxy(player->x, player->y);
    textcolor(LIGHTGRAY);
    putch(CH_SMILY1);

    if (!item_collected) { //could this be dryer like an array?
        gotoxy(flat->x, flat->y);
        textcolor(MAGENTA);
        putch(CH_LETTER_B);
        gotoxy(sharp->x, sharp->y);
        textcolor(RED);
        putch(CH_POUND);
        gotoxy(natural->x, natural->y);
        textcolor(CYAN);
        putch(CH_NAK);
    }     
}


void collect_gem(player_t *player, entities_t *flat, entities_t *sharp, entities_t *natural)
{
    if ( !item_collected && sharp->x == player->x && sharp->y == player->y ) {  // player is on gem!
        // do collect gem stuff
        item_collected = true;
        sound_collect();
        gotoxy(player->x, player->y);
        textcolor(LIGHTGRAY);
        putch(CH_SMILY1);
    } 
    
}

void draw_random_entities(player_t *player, entities_t *flat, entities_t *sharp, entities_t *natural)
{

        player->x = (rand() % 20) + 1;
        player->y = (rand() % 20) + 1;

        flat->x = (rand() % 20) + 1;
        flat->y = (rand() % 20) + 1;

        sharp->x = (rand() % 20) + 1;
        sharp->y = (rand() % 20) + 1;

        natural->x = (rand() % 20) + 1;
        natural->y = (rand() % 20) + 1;
}

void key_hit(player_t *player, entities_t *flat, entities_t *sharp, entities_t *natural) // this function: every time a hit is hit
{
    
    clrscr();
    int key = getch();
    
    switch (key) {
        case 'w': // TODO: optimize logic for wasd
            --player->y;
            if (player->y < MIN_Y) {
                player->y = MIN_Y;
            }    
            break;
        case 's':
            ++player->y;
            if (player->y > MAX_Y) {
                player->y = MAX_Y;
            }    
            break;
        case 'a':
            --player->x;
            if (player->x < MIN_X) {
                player->x = MIN_X;
            }    
            break;
        case 'd':
            ++player->x;
            if (player->x > MAX_X) {
                player->x = MAX_X;
            }    
            break;
        default:
            break;
    }
    // TODO: the player has moved, does something happen?
   
    draw_level(player, flat, sharp, natural); // TODO: this is good, keep it
    collect_gem(player, flat, sharp, natural);
    
    if (item_collected && sharp->x != player->x && sharp->y != player->y) {
        item_collected = false;
        clrscr();
        draw_random_entities(player, flat, sharp, natural);
        draw_level(player, flat, sharp, natural);
    } 
    
}

int main()
{
    textmode(C40);
    setcursor(0);
    setscreensize(SCREEN_W, SCREEN_H);
    initdos();
    
    srand((unsigned)time(NULL));
    
    player_t player;
    entities_t flat;
    entities_t sharp;
    entities_t natural;
    
    draw_random_entities(&player, &flat , &sharp, &natural);
    

    draw_level(&player, &flat, &sharp, &natural);
    
    while (1) {
        
        if (kbhit()) {
            key_hit(&player, &flat, &sharp, &natural);
           
    

        }
        refresh();
    }    
    
    return 0;
}
