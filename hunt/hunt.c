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

#include "play.h"
#include "utility.h"
#include "ascii.h"

#include <dos.h>
#include <conio.h>

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


// =============================================================================
// DEFINES

#define SCREEN_W    20
#define SCREEN_H    20

// note: minimum x and y is 1 in turbo C
#define MAX_X       SCREEN_W
#define MAX_Y       SCREEN_H

#define MIN_X           1
#define MIN_Y           1
#define MAX_NUM_ITEMS   3
// =============================================================================
// STRUCTS / TYPES / ENUMS


typedef struct
{
    int x;
    int y;
    
    // TODO: appearance
    int ch;
    int color;
    
    // TODO: entity's state
    bool active;
} entity_t;

// TODO: function that makes a new entity_t
// TODO: draw entity function

// =============================================================================
// DATA (state) global variables are initialized to 0 by default

entity_t player;

entity_t flat;
entity_t sharp;
entity_t natural;

entity_t entities[3] = {ASCII_FACE1, 'b', '#', ASCII_SECTION};

entity_t color[3] = {LIGHTGRAY, MAGENTA, RED, CYAN};
bool item_collected = false; // this gets replaced with struct member (active)



// =============================================================================
// FUNCTIONS
void print_objective()
{
    gotoxy(MIN_X, MIN_Y);
    textcolor(YELLOW);
    cprintf("G%c", ASCII_UPARROW);
}

void sound_collect()
{
    const int tempo = 220; 
    const int note_value = 16; 
    const int octave = 4; 
    
    for (int i = 0; i < 2; i++) {
        play(NOTE_G, octave, note_value, tempo);
        play(NOTE_G_SHARP, octave, note_value, tempo);
    }

}

void draw_level()
{
    print_objective();
    
    gotoxy(entities[0].x, entities[0].y);
    textcolor(LIGHTGRAY);
    putch(ASCII_FACE1);

    if (!item_collected) { //could this be dryer like an array?
        
        gotoxy(entities[1].x, entities[1].y);
        textcolor(MAGENTA);
        putch('b');
        gotoxy(entities[2].x, entities[2].y);
        textcolor(RED);
        putch('#');
        gotoxy(entities[3].x, entities[3].y);
        textcolor(CYAN);
        putch(ASCII_SECTION);
    }     
}


void collect_gem()
{
    if ( !item_collected && entities[2].x == entities[0].x && entities[2].y == entities[0].y ) {  // player is on gem!
        // do collect gem stuff
        item_collected = true;
        sound_collect();
        gotoxy(entities[0].x, entities[0].y);
        textcolor(LIGHTGRAY);
        putch(ASCII_FACE1);
    } 
    
}

// returns a random coordinate between 1 and max_value
int random_coord(int max_value)
{
    return (rand() % max_value) + 1;
}

void draw_random_entities()
{
    // this is the new version
    for (int i = 0; i <= 3; i++)
    {
        entities[i].x = random_coord(SCREEN_W);
        entities[i].y = random_coord(SCREEN_H);
    }
    
}

void key_hit() // this function: every time a hit is hit
{
    
    clrscr();
    int key = getch();
    
    switch (key) {
        case 'w': // TODO: optimize logic for wasd (clamp, from utility.h)
            --entities[0].y;
            if (entities[0].y < MIN_Y) {
                entities[0].y = MIN_Y;
            }    
            break;
        case 's':
            ++entities[0].y;
            if (entities[0].y > MAX_Y) {
                entities[0].y = MAX_Y;
            }    
            break;
        case 'a':
            --entities[0].x;
            if (entities[0].x < MIN_X) {
                entities[0].x = MIN_X;
            }    
            break;
        case 'd':
            ++entities[0].x;
            if (entities[0].x > MAX_X) {
                entities[0].x = MAX_X;
            }    
            break;
        default:
            break;
    }
    // the player has moved (potentially)
   
    draw_level(); // TODO: this is good, keep it
    collect_gem();
    
    if (item_collected && entities[2].x != entities[0].x && entities[2].y != entities[0].y) {
        item_collected = false;
        clrscr();
        draw_random_entities();
        draw_level();
    } 
    
}

int main()
{
    textmode(C40);
    setcursor(0);
    setscreensize(SCREEN_W, SCREEN_H);
    initdos();
    
    srand((unsigned)time(NULL));
    
    // TODO: set entities' appearance
    
    draw_random_entities();
    draw_level();
    
    // game loop structure:
    // 1. get and handle inputs (keyboard, mouse)
    // 2. update the game (logic stuff)
    // 3. redraw
    while (1) {
        
        if (kbhit()) {
            key_hit();
        }
        
        refresh();
    }    
    
    return 0;
}
