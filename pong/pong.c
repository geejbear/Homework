// TODO: heading
//

//:i TODOs
// > inline TODOs (do a search 'TODO')
// - copy over play source code files
// - think about is clamp a useful thing to have
// - serve state, play state
// - - serve: ball position is reset
// - - serve: ball stays until key press to start round
// - - play: ball goes off side: set to serve state, reset ball

// NOTES
// - ...

// BUGS

// "" includes: relative to current path
// <> includes: where the compiler looks for headers (-I)
#include <play.h>
#include <utility.h>
#include <ascii.h>
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
#define PADDLE_SIZE     3
#define SERVE_COUNTER   3
#define CHAR_BALL       7

// game data

enum
{
    STATE_SERVE = 1,
    STATE_RUMBLE,
};

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    char ch;
    int color;
    bool serve;
} GameObject;


// initialize a struct all at once
GameObject ball = { 
    .x = SCREEN_W / 2, 
    .y = SCREEN_H / 4, 
    .dx = 1, 
    .dy = 1,
    .ch = CHAR_BALL,
    .color = WHITE, 
    .serve = false,
};

GameObject paddle_left = { 
    .x = MIN_X,
    .y = SCREEN_H/2,
    .dx = 0,
    .dy = 0,
    .ch = CHAR_PADDLE,
    .color = GREEN, 
    .serve = false,
};

GameObject paddle_right = { 
    .x = MAX_X, 
    .y = SCREEN_H/2, 
    .dx = 0, 
    .dy = 0,
    .ch = CHAR_PADDLE,
    .color = RED, 
    .serve = false,
};

void KeepObjectInBounds( GameObject * paddle )
{
    clamp(&paddle->y, MIN_Y, MAX_Y - 2);
}

bool GetInput(int key)
{
    switch (key) {
        case 'w': --paddle_left.y; break;
        case 's': ++paddle_left.y; break;
        case 'i': --paddle_right.y; break;
        case 'k': ++paddle_right.y; break;
        default: break;
    }
    
    KeepObjectInBounds(&paddle_right);
    KeepObjectInBounds(&paddle_left);
    
    return true;
}

// TODO: MoveBallToPreviousPosition
void MoveBallToPreviousPosition() 
{
    ball.x -= ball.dx;  // put it back
    ball.y -= ball.dy;  // put it back
}

void UpdateGame()
{
    ball.serve = true;
    
    
    if (ball.serve == false) {
        ball.x += ball.dx;        
        ball.y += ball.dy;
    }
    
    // handle whether ball when off screen:
    
    // TEMP
    // ball went off right or left side of screen?
    if ( ball.x == MAX_X + 1 || ball.x == MIN_X - 1 )  {
        ball.serve = true;
        ball.x = SCREEN_W / 2; 
        ball.y = SCREEN_H / 4;
        ball.serve = false;   
    }
    
    // ball went off top or bottom side of screen?
    if ( ball.y == MAX_Y + 1 || ball.y == MIN_Y - 1 ) {
        MoveBallToPreviousPosition();
        ball.dy = -ball.dy;
    }

    int hit_ch = getscreench(ball.x, ball.y);
    if (hit_ch == CHAR_PADDLE) {
        MoveBallToPreviousPosition();
        play(NOTE_C, 4, 4, 120);
        ball.dx = - ball.dx;
    }    

}

void DrawPaddle(GameObject * paddle)
{
    textcolor(paddle->color);

    for ( int y = paddle->y; y < paddle->y + PADDLE_SIZE; y++ ) {
        gotoxy(paddle->x, y);
        putch(paddle->ch);
    }
}

void DrawGame()
{
    clrscr();
    gotoxy(ball.x, ball.y);
    textcolor(WHITE);
    putch(7);


    DrawPaddle(&paddle_left);
    DrawPaddle(&paddle_right);
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

        if ( ticks % 10 == 0 ) {
            UpdateGame();
            DrawGame();
        }
        
        refresh();
        ticks++;
    }
    
    return 0;
}
