#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <textmode.h>
#include <stdbool.h>

#define CONSOLE_W 20
#define CONSOLE_H 20
#define CONSOLE_SIZE (CONSOLE_W * CONSOLE_H)

// alternative: const char * map = { ...
int map[CONSOLE_H][CONSOLE_W] = {
    { 1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};

int main()
{
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        fprintf(stderr, "Error: SDL_Init() failed! (%s)\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    DOS_InitScreen("Bounder", CONSOLE_W, CONSOLE_H, DOS_MODE40, 4);
    DOS_SetScreenScale(3);
    DOS_SetCursorType(DOS_CURSOR_NONE);
    
    int player_x = CONSOLE_W / 2;
    int player_y = CONSOLE_H / 2;

    
    // program loop:
    bool running = true;
    while ( running ) {
        DOS_LimitFrameRate(30);
        
        // 1) get input
        SDL_Event event;
        while ( SDL_PollEvent(&event) ) {
            switch ( event.type ) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if ( event.key.keysym.sym == SDLK_UP) {
                        player_y--;
                    }
                    if ( event.key.keysym.sym == SDLK_LEFT) {
                        player_x--;
                    }
                default:
                    break;
            }
        }

        // 2) update game
        
        // 3) draw game
        DOS_ClearScreen();
        
        for ( int y = 0; y < CONSOLE_H; y++ ) {
            for ( int x = 0; x < CONSOLE_W; x++ ) {
                if ( map[y][x] ) {
                    DOS_GotoXY(x, y);
                    DOS_SetForeground(DOS_GRAY);
                    DOS_PrintChar(219);
                }
            }
        }
        
        // draw player
        DOS_GotoXY(player_x, player_y);
        DOS_SetForeground(DOS_YELLOW);
        DOS_PrintChar(DOS_FACE1);
        
        DOS_DrawScreen();
    }
    
    // exit program:
    
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
