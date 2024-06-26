#include "render.hh"
#include <stdio.h>

int main(int argc, char* args[]) {
    // A janela
    SDL_Window* window = NULL;

    if (not initWindow(&window)) {
        // Something went wrong initializing window
        return 1;
    }

    initCamera();

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Error: %s", SDL_GetError());
        return 1;
    }
    addObjects();

    //Hack to get window to stay up
    SDL_Event e; 
    bool quit = false; 
    while( !quit ) {
        while( SDL_PollEvent( &e ) ) {
            if ( e.type == SDL_QUIT )
                quit = true;
            // elif (e.key == SDL_KEY)
        }

        update(&window, &renderer);
    }
    // End Execution
    close( &window );
    return 0;
}
