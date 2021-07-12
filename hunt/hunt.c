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

// =============================================================================
// STRUCTS / TYPES / ENUMS

enum
{
    ENT_PLAYER,
    ENT_FLAT,
    ENT_SHARP,
    ENT_NATURAL,
    ENT_NUM_ENTITIES
};

typedef struct
{
    int x;
    int y;
    int ch;
    int color;
    bool active; // gems: active = on the board
} entity_t;

// TODO: function that makes a new entity_t
// TODO: draw entity function

// =============================================================================
// DATA (state) global variables are initialized to 0 by default

entity_t entities[ENT_NUM_ENTITIES];

// the values that are used to initialize each entities .ch and .color members
// (the default values)
const int colors[ENT_NUM_ENTITIES] = {LIGHTGRAY, MAGENTA, RED, CYAN};
const int items[ENT_NUM_ENTITIES] = {ASCII_FACE1, 'b', '#', ASCII_SECTION};



// =============================================================================
// FUNCTIONS

void print_objective()
{
    gotoxy(MIN_X, MIN_Y);
    textcolor(YELLOW);
    cprintf("G%c", ASCII_UPARROW);
}

// TODO: try var note, and note + 1 or genericness, or note param
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

// TODO: draw entity function

void draw_entities()
{
    for (int i = 0; i < ENT_NUM_ENTITIES; i++) {
        
        if ( !entities[i].active ) {
            continue;
        }
        
        gotoxy(entities[i].x, entities[i].y);
        textcolor(colors[i]);
        putch(items[i]);
    }
}


// returns a random coordinate between 1 and max_value
int random_coord(int max_value)
{
    return (rand() % max_value) + 1;
}

void ranomize_entity_coords()
{
    // this is the new version
    for (int i = 0; i < ENT_NUM_ENTITIES; i++)
    {
        entities[i].x = random_coord(SCREEN_W);
        entities[i].y = random_coord(SCREEN_H);
    }
}

void keep_in_bounds(int *x, int *y)
{
    clamp(x, MIN_X, SCREEN_W);
    clamp(y, MIN_Y, SCREEN_H);
}

bool are_entities_overlapping(entity_t *e1, entity_t *e2)
{
    return e1->x == e2->x && e1->y == e2->y;
}

void draw_everything()
{
    clrscr();
    print_objective();
    draw_entities();
}

// TODO: Objective: Collect a ? (sharp, flat, natural)
// maybe: Sharps: 3 Flat: 5 Naturals: 10

void update_game()
{
    // (for readability)
    entity_t * player = &entities[ENT_PLAYER];
    entity_t * sharp = &entities[ENT_SHARP];
    
    if ( are_entities_overlapping(player, sharp) ) {
        
        sharp->active = false; // collected it
   
        draw_everything(); // hack so that you see the player on the gem spot
        refresh();
        sound_collect();
        sleep(1);
        
        ranomize_entity_coords();
        sharp->active = true; // uncollect it
    } 
}

void key_hit(int key) 
{
    switch (key) { // TODO: use enum values (ENT_PLAYER instead of 0)
        case 'w': --entities[0].y; break;
        case 's': ++entities[0].y; break;
        case 'a': --entities[0].x; break;
        case 'd': ++entities[0].x; break;
        default: break;
    }
    
    keep_in_bounds(&entities[0].x, &entities[0].y);  
}

int main()
{
    setscale(4);
    textmode(C40);
    setcursor(0);
    setscreensize(SCREEN_W, SCREEN_H);
    initdos();
    
    srand((unsigned)time(NULL));
    
    // TODO: set entities' appearance

    // assign each entity its default color
    for ( int i = 0; i < ENT_NUM_ENTITIES; i++ ) {
        entities[i].ch = items[i];
        entities[i].color = colors[i];
        entities[i].active = true;
    }

    ranomize_entity_coords();
    
    draw_everything();
        
    // game loop structure, every frame:
    // 1. get and handle inputs (keyboard, mouse)
    // 2. update the game (logic stuff)
    // 3. redraw
    while (1) {
        
        if (kbhit()) {
            key_hit(getch());
            update_game();
            draw_everything();
        }
        
        refresh();
    }    
    
    return 0;
}
