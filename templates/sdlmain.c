#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int main()
{
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        fprintf(stderr, "Error: SDL_Init() failed! (%s)\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    // initialize a window:
    
    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;
    
    SDL_Window * window = SDL_CreateWindow("SDL Template", x, y, 640, 480, 0);
    
    if ( window == NULL ) {
        fprintf(stderr, "Error: SDL_CreateWindow() failed! (%s)\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    // initialize a renderer:
    
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    if ( renderer == NULL ) {
        fprintf(stderr, "Error: SDL_CreateRenderer() failed! (%s)\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // program loop:
    bool running = true;
    while ( running ) {
        
        SDL_Event event;
        while ( SDL_PollEvent(&event) ) {
            switch ( event.type ) {
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        
        // clear screen:
        SDL_SetRenderDrawColor(renderer, 0x10, 0x10, 0xFA, 0x70);
        SDL_RenderClear(renderer);

        // all rendering:
        // ...

        // look up types: SDL_Point, SDL_Rect
        // try SDL_RenderDrawPoint, SDL_RenderDrawLine, SDL_RenderFillRect

        SDL_RenderPresent(renderer);
        
        // 60 fps, how many ms should each frame take?
        SDL_Delay(15);
    }
    
    // exit program:
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
