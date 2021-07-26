//
// TODO: heading
//

// TODOs
// > inline TODOs (do a search 'TODO')
// - copy over play source code files
// - think about is clamp a useful thing to have

// NOTES
// - ...

// BUGS
// - ...

#include <dos.h>
#include <conio.h>
#include "play.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#define SCREEN_W    16
#define SCREEN_H    16
// note: minimum x and y is 1 in turbo C
#define MAX_X       SCREEN_W
#define MAX_Y       SCREEN_H
#define MIN_X           1
#define MIN_Y           1

// game data

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
} ball_t;

// initialize a struct all at once
ball_t ball = { SCREEN_W / 2, SCREEN_H / 4, 1, 1 };
    
void GetInput(int key)
{
    switch (key) {
        case 'w': --ball.y; break;
        case 's': ++ball.y; break;
        case 'a': --ball.x; break;
        case 'd': ++ball.x; break;
        default: break;
    }
}

void BounceBallBack() 
{
    ball.x -= ball.dx;  // put it back
    ball.y -= ball.dy;  // put it back
}

void UpdateGame()
{
    // update the ball's position
    ball.x += ball.dx;
    ball.y += ball.dy;
    
    // TODO: optomize / DRY:
    
    // handle whether ball when off screen:
    
    if (( ball.x > MAX_X ) || (ball.x < MIN_X))  { 
        // ball went off right side of screen
        BounceBallBack();
        ball.dx = -ball.dx; // bounce it back
    }
    
    if (( ball.y > MAX_Y ) || (ball.y < MIN_Y)) { // ball went off right side of screen
        BounceBallBack();
        ball.dy = -ball.dy; // bounce it back
    }

    // TODO: handle ball off screen top and left
}


    

void DrawGame()
{
    clrscr();
    gotoxy(ball.x, ball.y);
    putch(7);
}

int main()
{
    setscale(4);
    textmode(C40);
    setcursor(0);
    setscreensize(SCREEN_W, SCREEN_H);
    initdos();
    
    int ticks = 0;
    while (1) {
        
        if ( kbhit() ) {
            GetInput(getch());
        }

        if (ticks % 10 == 0 ) {
            UpdateGame();
        }
        
        DrawGame();
        
        refresh();
        ticks++;
    }
    
    return 0;
}
