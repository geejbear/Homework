#include "entity.h"

#include <dos.h>
#include <conio.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define GAME_W          20 // the 'play area'
#define GAME_H          20
#define STATUS_LINE     (GAME_H + 1)

#define NUM_GEMS        4

#define CHAR_FACE       2
#define CHAR_DIAMOND    4

// =============================================================================
// DATA

entity_t player;
entity_t gems[NUM_GEMS];
int gem_colors[NUM_GEMS] = { LIGHTRED, LIGHTGREEN, LIGHTCYAN, LIGHTMAGENTA };
int num_gems_collected;

// =============================================================================
// FUNCTIONS

void tf_clamp(int *value, int min, int max)
{
    if ( *value < min ) {
        *value = min;
    } else if ( *value > max ) {
        *value = max;
    }
}


void keep_in_bounds(int *x, int *y)
{
    tf_clamp(x, 1, GAME_W);
    tf_clamp(y, 1, GAME_H);
}


int random_x()
{
    return (rand() % GAME_W) + 1;
}


int random_y()
{
    return (rand() % GAME_H) + 1;
}


void handle_key(int key)
{
    switch ( key )
    {
        case 27: exit(0); // escape
        case 'w': player.y--; break;
        case 'a': player.x--; break;
        case 's': player.y++; break;
        case 'd': player.x++; break;
        
        default: return;
    }
    
    keep_in_bounds(&player.x, &player.y);
}


void update_game()
{
    // check each gem: player there?
    
    for ( int i = 0; i < NUM_GEMS; i++ ) {
        // current gem: gems[i]
        if ( entities_overlap(&player, &gems[i]) && gems[i].active) {
            // collect it
            gems[i].active = false;
            num_gems_collected++;
            sound(600, 50);
            sound(800, 50);
        }
    }
}


void draw_status_bar(int y)
{
    textbackground(BLUE);
    textcolor(WHITE);
    for ( int x = 1; x <= GAME_W; x++ ) { // clear/fill entire line
        gotoxy(x, y);
        putch(' ');
    }
    gotoxy(1, y);
    cprintf("GEMS COLLECTED: %d", num_gems_collected);
}


void redraw_game()
{
    clrscr();
    draw_status_bar(STATUS_LINE);    
    draw_entity(&player);
    
    for ( int i = 0; i < NUM_GEMS; i++ ) {
        draw_entity(&gems[i]);
    }
}


int main()
{
    srand((unsigned)time(NULL));
    
    // init LibTC
    textmode(C40);
    setscreensize(GAME_W, GAME_H + 1); // 1 extra for status line
    setscale(2);
    setcursor(CURSOR_NONE);
    setbordercolor(BLUE);
    setname("The Hunt");
    setbordersize(2);
    initdos();

    // initialize all entities
    // TODO: make sure entities don't overlap!    
    player  = new_entity(GAME_W/2, GAME_H/2, CHAR_FACE, YELLOW, BLACK);
    
    for ( int i = 0; i < NUM_GEMS; i++ ) {
        int x = random_x();
        int y = random_y();
        gems[i] = new_entity(x, y, CHAR_DIAMOND, gem_colors[i], BLACK);
    }
    
    redraw_game(); // make sure everything appears before first key press
    
    // game loop
    while ( 1 ) {
        if ( kbhit() ) {        
            handle_key(getch());
            update_game(); // process any changes
            redraw_game(); // display changes
        }
        refresh();
    }
}
