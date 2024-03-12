
#define SDL_MAIN_HANDLED // avoid  "undefined reference to 'WinMain'"

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "../include/tetris_asset.h"

using namespace std;

static bool init();
static void kill();
static bool load();
static bool loop();

// Variables to hold our window and surfaces
static SDL_Window* window;
static SDL_Renderer* mainRenderer;
static SDL_Texture* block;
static TTF_Font* mainFont;

static int cx = 0;
static int cy = 0;
static unsigned int idxBlock = 0;
static int SPRITE_WIDTH = 256;
static int SPRITE_HEIGHT = 256;
static int angle = 0;

using namespace std;


static void loadBlock(){
    block = IMG_LoadTexture(mainRenderer,"assets/blocks/J2.png");
    if( !block ){
        cout << "Error creating texture: " << SDL_GetError() << endl;
        system("pause");
        return ;
    }
}


int main_loading_assets(int argc, char** args) {

    if ( !init() ) return 1;

    if ( !load() ) return 1;

    loadAssets(mainRenderer);


    while ( loop() ) {
        // wait before processing the next frame
        SDL_Delay(10);
    }

    kill();
    return 0;
}

 static bool loop() {

    SDL_Event e;

    SDL_Rect rect;
    rect.w = SPRITE_WIDTH;
    rect.h = SPRITE_HEIGHT;
    rect.x = cx;
    rect.y = cy;

    SDL_Color textColor;
    textColor.a = 0; //#C9E7F2
    textColor.b = 0xF2;
    textColor.g = 0xE7;
    textColor.r = 0xC9;
        SDL_SetRenderDrawColor(
                mainRenderer, textColor.r, textColor.g, textColor.b, textColor.a
        );
    SDL_Surface* text = TTF_RenderText_Solid(mainFont, "This is T E T R I S", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mainRenderer,text);
    t_image* blocks = getAssets();
    int const NBLOCK = getNAssets();//sizeof(blocks)/sizeof(t_image);

    while( SDL_PollEvent( &e ) != 0 ) {
        switch (e.type) {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym){
                    case SDLK_w: cy -= 5; break;
                    case SDLK_s: cy +=5; break;
                    case SDLK_a: cx -=5; break;
                    case SDLK_d: cx +=5; break;
                    case SDLK_q: angle +=-90; break;
                    case SDLK_e: angle +=90; break;
                    case SDLK_x: idxBlock =  (idxBlock + 1 ) % NBLOCK; break;
                    case SDLK_z: idxBlock =  (idxBlock - 1 ) % NBLOCK; break;
                }
            case SDL_KEYUP:
                break;
            case SDL_MOUSEMOTION:
                break;
        }
        SDL_RenderClear(mainRenderer);

        SDL_SetRenderDrawColor(
                mainRenderer,
                0xA0, 0xA0, 0xA0, 0xFF
        );

        //SDL_RenderCopy(mainRenderer, block, NULL, &rect);
        rect.w = blocks[idxBlock].width;
        rect.h = blocks[idxBlock].height;
        SDL_RenderCopyEx(mainRenderer, blocks[idxBlock].texture, NULL, &rect,
                         angle, NULL, SDL_FLIP_NONE);
        SDL_Rect textBox;
        textBox.x = textBox.y = 0;
        textBox.w = 200;
        textBox.h = 18;
        SDL_RenderCopy(mainRenderer, textTexture, NULL, &textBox);
        /*
        SDL_RenderFillRect(
                mainRenderer,
                &rect
        );
         */
        cout<<idxBlock<<":"<<blocks[idxBlock].origin<<" "<<rect.h<<" "<<rect.w<<" "<<rect.x<<" "<<rect.y<<endl;

        SDL_RenderPresent(mainRenderer);
    }



    return true;
}

bool load() {
    loadBlock();

    mainFont = TTF_OpenFont("assets/fonts/ka1.ttf", 26);
    if( mainFont == NULL ) {
        cout << "Error loading Font: " << TTF_GetError() << endl;
        system("pause");
        return false;
    }

    return true;
}

bool init() {
    // See last example for comments
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        system("pause");
        return false;
    }

    if ( TTF_Init() < 0 ){
        cout << "Error initializing TTF Failed: " << TTF_GetError() << endl;
        system("pause");
        return false;
    }

    if ( IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0 ) {
        cout << "Error initializing SDL Image: " << IMG_GetError() << endl;
        system("pause");
        return false;
    };

    window = SDL_CreateWindow( "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               1280, 720, SDL_WINDOW_RESIZABLE );
//                               SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE);
    if ( !window ) {
        cout << "Error creating window: " << SDL_GetError()  << endl;
        system("pause");
        return false;
    }

    mainRenderer = SDL_CreateRenderer( window, -1 , SDL_RENDERER_ACCELERATED );
    if ( !mainRenderer ) {
        cout << "Error getting renderer: " << SDL_GetError() << endl;
        system("pause");
        return false;
    }
    return true;
}

void kill() {
    SDL_SetRenderDrawColor( mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( mainRenderer );
    // Quit
    SDL_DestroyWindow( window );
    SDL_Quit();
}

int main(int argc,char** args){
    exit(main_loading_assets(argc,args));
}
