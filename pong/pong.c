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
// - paddle blinks when it reaches clamp limit

// "" includes: relative to current path
// <> includes: where the compiler looks for headers (-I)
#include <play.h>
#include <utility.h>
#include "ascii.h"

#include <dos.h>
#include <conio.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#define SCREEN_W        16
#define SCREEN_H        16
// note: minimum x and y is 1 in turbo C
#define MAX_X           SCREEN_W
#define MAX_Y           SCREEN_H
#define MIN_X           1
#define MIN_Y           1
#define CHAR_PADDLE     10
#define PADDLE_SIZE     3


// game data

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    char ch;
    int color;
} GameObject;


// initialize a struct all at once
GameObject ball = { 
    SCREEN_W / 2, 
    SCREEN_H / 4, 
    1, 
    1,
    0,
    0, 
};

GameObject paddle_left = { 
    MIN_X, 
    SCREEN_H/2, 
    0, 
    0,
    CHAR_PADDLE,
    RED, 
};

GameObject paddle_right = { 
    MAX_X, 
    SCREEN_H/2, 
    0, 
    0,
    CHAR_PADDLE,
    GREEN, 
};


void GetInput(int key)
{
    switch (key) {
        case 'w': --paddle_left.y; break;
        case 's': ++paddle_left.y; break;
        case 'i': --paddle_right.y; break;
        case 'k': ++paddle_right.y; break;
        case 't': {
            int ch = (unsigned)getscreench(paddle_left.x, paddle_left.y);
            printf("ch is: %d\n", ch);
            break;
        }
        default: break;
    }
}

// TODO: MoveBallToPreviousPosition
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
    
    if (( ball.x == MAX_X + 1 ) || (ball.x == MIN_X - 1))  { 
        // ball went off right side of screen
        BounceBallBack();
        ball.dx = -ball.dx; // bounce it back
    }
    
    if (( ball.y == MAX_Y + 1 ) || (ball.y == MIN_Y - 1)) { // ball went off right side of screen
        BounceBallBack();
        ball.dy = -ball.dy; // bounce it back
    }


    // TODO: handle ball off screen top and left
}

void BallAndPaddleOverlap()
{
     //bounce back if paddle hits ball
    if (ball.y == paddle_left.y && ball.x == paddle_left.x)  {
        //ball.x++;
        //BounceBallBack();
        play(NOTE_C, 4, 4, 120);
        //ball.dy = -ball.dy;
    }
}

void KeepPaddleInBounds(int loc_x, int loc_y, int *x, int *y, int *z)
{
    clamp(x, loc_x, loc_y);
    clamp(y, MIN_Y, MAX_Y);
    clamp(z, MIN_Y - 2, MAX_Y - 2);
}

/*
 Alt approach
L PADDLE: 10
 10
 11
 12
 
 for ( int y = paddle.y; y < paddle.y + PADDLE_H; y++ )
 {
    gotoxy(paddle.x, y)
    ...
 }
 
*/

void DrawRightPaddle()
{
    gotoxy(paddle_right.x, paddle_right.y);
    textcolor(GREEN);
    
    int count = 1;
    
    // gotoxy is the answer for location, i is already the counter for y
    for (int i = 0; i < PADDLE_SIZE; i++) {
        putch(CHAR_PADDLE);
        cprintf("\n");
        gotoxy(paddle_right.x, paddle_right.y + count);
        count++;
    }    
    KeepPaddleInBounds(MAX_X, MAX_Y, &paddle_right.x, &paddle_right.y, &paddle_right.y);
}

void DrawLeftPaddle() 
{
    gotoxy(paddle_left.x, paddle_left.y);
    textcolor(RED);
    
    for (int i = 0; i < PADDLE_SIZE; i++) {
        putch(CHAR_PADDLE);
        cprintf("\n");
    }

    KeepPaddleInBounds(MIN_X, MIN_Y, &paddle_left.x, &paddle_left.y, &paddle_left.y);
}


void DrawGame()
{
    clrscr();
    gotoxy(ball.x, ball.y);
    textcolor(WHITE);
    putch(7);

    DrawLeftPaddle();
    DrawRightPaddle();
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
