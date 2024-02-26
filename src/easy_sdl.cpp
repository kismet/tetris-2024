//Using SDL and standard IO
#include "../include/easy_sdl.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;

static SDL_Renderer* mainRenderer = NULL;
static SDL_Window* window = NULL;

SDL_Window* getSDLWindow(){
    return window;
}

SDL_Renderer* getSDLRender() {
    return mainRenderer;
}

bool initEasySDL(char* title, int width, int height, int options ){
    //TODO Free SDL, TTF, and IMG on failure
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        cerr<< "Error initializing SDL: " << SDL_GetError() << endl;
        return false;
    }

    if ( TTF_Init() < 0 ){
        cerr << "Error initializing TTF Failed: " << TTF_GetError() << endl;
        return false;
    }

    if ( IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0 ) {
        cerr << "Error initializing SDL Image: " << IMG_GetError() << endl;
        return false;
    };

    if (options == 0 )  {
        window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   height, width, SDL_WINDOW_RESIZABLE );
    }else{
        window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   height, width, options );
    }
    if ( !window ) {
        cerr << "Error creating window: " << SDL_GetError()  << endl;
        return false;
    }

    mainRenderer = SDL_CreateRenderer( window, -1 , SDL_RENDERER_ACCELERATED );
    if ( !mainRenderer ) {
        cerr << "Error getting renderer: " << SDL_GetError() << endl;
        return false;
    }
/* Cleaning
    SDL_RenderClear( mainRenderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
*/
    return true;
}




