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

#define SCREEN_W    16
#define SCREEN_H    16

// note: minimum x and y is 1 in turbo C
#define MAX_X       SCREEN_W
#define MAX_Y       SCREEN_H

#define MIN_X           1
#define MIN_Y           1

#define MAX_NUM_ITEMS   4

// =============================================================================
// STRUCTS / TYPES / ENUMS


typedef struct
{
    int x;
    int y;
    int ch;
    int color;
    bool active;
} entity_t;

// TODO: function that makes a new entity_t
// TODO: draw entity function

// =============================================================================
// DATA (state) global variables are initialized to 0 by default

entity_t entities[MAX_NUM_ITEMS]; 
int colors[MAX_NUM_ITEMS] = {LIGHTGRAY, MAGENTA, RED, CYAN};
int items[MAX_NUM_ITEMS] = {ASCII_FACE1, 'b', '#', ASCII_SECTION}; 

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
    
    if (!item_collected) { //could this be dryer like an array?
        for (int i = 0; i < MAX_NUM_ITEMS; i++) {
            gotoxy(entities[i].x, entities[i].y);
            textcolor(colors[i]);
            putch(items[i]);
        }    
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

void keep_in_bounds(int x, int y)
{
    clamp(x, MIN_X, SCREEN_W);
    clamp(y, MIN_Y, SCREEN_H);
}

void redraw_level()
{
    draw_level(); // TODO: this is good, keep it
    collect_gem();
    
    if (item_collected && entities[2].x != entities[0].x && entities[2].y != entities[0].y) {
        item_collected = false;
        clrscr();
        draw_random_entities();
        draw_level();
    } 
}

void key_hit(int key) 
{
    switch (key) {
        case 'w': --entities[0].y; break;
        case 's': ++entities[0].y; break;
        case 'a': --entities[0].x; break;
        case 'd': ++entities[0].x; break;
        default: break;

    }
    
    clamp(entities[0].x, MIN_X, SCREEN_W);
    //keep_in_bounds(entities[0].x, entities[0].y);
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
            clrscr();
            key_hit(getch());
            redraw_level();
        }
        
        refresh();
    }    
    
    return 0;
}
