#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600, SCALE = 1;

int main (int argc, char *argv[]) {
    
    printf("Initialising Video");
    SDL_Init(SDL_INIT_VIDEO);

    printf("Creating Window");
    SDL_Window *window = SDL_CreateWindow("The Game Of Life", 
                                            100, 
                                            100, 
                                            WIDTH * SCALE, 
                                            HEIGHT * SCALE, 
                                            SDL_WINDOW_ALLOW_HIGHDPI);
    // Check window is created
    if ( NULL == window)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    printf("Creating Render");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 
                            -1,
                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    printf("Cleaing Renderer");
    SDL_RenderClear(renderer);

    printf("Creating base texture");
    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                            SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            WIDTH,
                                            HEIGHT);
    printf("Creating Boards");

    SDL_Event windowEvent;


    bool quit = false;
    while (!quit)
    {
        if ( SDL_PollEvent (&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            { 
                break; 
            }
        }
    }
    SDL_DestroyWindow (window);
    SDL_Quit( );

    return EXIT_SUCCESS;
}