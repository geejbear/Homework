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

#define INITIAL_BALL_X  (SCREEN_W * 0.5)
#define INITIAL_BALL_Y  (SCREEN_H * 0.75)

#define GAME_SPEED      10

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    char ch;
    int color;
    int score;
} GameObject;

GameObject ball = {
    .x = INITIAL_BALL_X,
    .y = INITIAL_BALL_Y,
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
    .color = RED,
    .score = 0
};

GameObject paddle_right = {
    .x = MAX_X,
    .y = SCREEN_H/2,
    .dx = 0,
    .dy = 0,
    .ch = CHAR_PADDLE,
    .color = GREEN,
    .score = 0
};


bool serve = true;


void SetServeState()
{
    serve = true;
    
    ball.x = INITIAL_BALL_X;
    ball.y = INITIAL_BALL_Y;
    ball.dx = 0;
    ball.dy = 0;
}


void SetPlayState()
{
    serve = false;
    
    ball.dx = arc4random_uniform(1000) < 500 ? 1 : -1;
    ball.dy = -1;
}


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
        case ' ':
            if ( serve ) {
                SetPlayState();
            }
            break;
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
    
    // handle whether ball when off screen:
    
    if ( ball.x == MAX_X + 1 ) {
        ++paddle_left.score;
        SetServeState();
    }
        
    if ( ball.x == MIN_X - 1 )  {
        ++paddle_right.score;
        SetServeState();
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
    
    textcolor(WHITE);
    
    gotoxy(SCREEN_W * 0.25, 1);
    cprintf("%d", paddle_left.score);
    
    gotoxy(SCREEN_W * 0.75, 1);
    cprintf("%d", paddle_right.score);
}


int main()
{
    setscale(4);
    textmode(C40);
    setcursor(0);
    setscreensize(SCREEN_W, SCREEN_H);
    initdos();
    
    SetServeState();
    
    bool running = true;
    int ticks = 0;
    while ( running ) {
        if ( kbhit() ) {
            running = GetInput(getch());
        }

        if (ticks % GAME_SPEED == 0 ) {
            UpdateGame();
            DrawGame();
        }
        
        refresh();
        ticks++;
    }
    
    return 0;
}
