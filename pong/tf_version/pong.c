#include <play.h>
#include <utility.h>

#include <dos.h>
#include <conio.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#define SCREEN_W        24
#define SCREEN_H        16

#define MIN_X           1
#define MIN_Y           1
#define MAX_X           SCREEN_W
#define MAX_Y           SCREEN_H

#define CHAR_BALL       7
#define CHAR_PADDLE     10

#define PADDLE_SIZE     3

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    char ch;
    int color;
} GameObject;

GameObject ball = {
    .x = SCREEN_W / 2,
    .y = SCREEN_H / 4,
    .dx = 1,
    .dy = 1,
    .ch = CHAR_BALL,
    .color = WHITE
};

GameObject paddle_left = {
    .x = MIN_X,
    .y = SCREEN_H/2,
    .dx = 0,
    .dy = 0,
    .ch = CHAR_PADDLE,
    .color = RED
};

GameObject paddle_right = {
    .x = MAX_X,
    .y = SCREEN_H/2,
    .dx = 0,
    .dy = 0,
    .ch = CHAR_PADDLE,
    .color = GREEN
};


void KeepPaddleInBounds(GameObject * paddle)
{
    clamp(&paddle->y, MIN_Y, MAX_Y - 2);
}


bool GetInput(int key)
{
    switch (key) {
        case 27: return false;
        case 'w': --paddle_left.y; break;
        case 's': ++paddle_left.y; break;
        case 'i': --paddle_right.y; break;
        case 'k': ++paddle_right.y; break;
        default: break;
    }
    
    // even though this is 'updating game' stuff, it's important that
    // the paddles are never in an invalid position, so do this right
    // after they've been moved
    KeepPaddleInBounds(&paddle_left);
    KeepPaddleInBounds(&paddle_right);
    
    return true;
}


void MoveBallToPreviousPosition()
{
    ball.x -= ball.dx;
    ball.y -= ball.dy;
}


void UpdateGame()
{
    // update the ball's position
    ball.x += ball.dx;
    ball.y += ball.dy;
    
    // TODO: optomize / DRY:
    
    // handle whether ball when off screen:
    
    // TEMP: ball went off right or left side of screen
    if ( ball.x == MAX_X + 1 || ball.x == MIN_X - 1 )  {
        MoveBallToPreviousPosition(); // correct its position
        ball.dx = -ball.dx; // bounce
    }
    
    // ball went off bottom or top of screen
    if ( ball.y == MAX_Y + 1 || ball.y == MIN_Y - 1) {
        MoveBallToPreviousPosition(); // correct its position
        ball.dy = -ball.dy; // bounce
    }
    
    // check for ball overlap with paddle
    int hit_ch = getscreench(ball.x, ball.y); // check what the ball's on
    if ( hit_ch == CHAR_PADDLE ) {
        MoveBallToPreviousPosition(); // move it back out of the paddle
        sound(1000, 50);
        ball.dx = -ball.dx; // reverse its horizontal movement
    }
}


void DrawGameObject(GameObject * game_object)
{
    textcolor(game_object->color);
    gotoxy(game_object->x, game_object->y);
    putch(game_object->ch);
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

    DrawGameObject(&ball);
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
    
    bool running = true;
    int ticks = 0;
    while ( running ) {
        if ( kbhit() ) {
            running = GetInput(getch());
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
