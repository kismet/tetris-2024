#define SDL_MAIN_HANDLED // avoid  "undefined reference to 'WinMain'"

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "../include/tetris_asset.h"
#include "../include/easy_sdl.h"

using namespace std;

char* assetsOrigin[] = {
        "assets/blocks/I.png",
        "assets/blocks/J.png",
        "assets/blocks/L.png",
        "assets/blocks/O.png",
        "assets/blocks/S.png",
        "assets/blocks/T.png",
        "assets/blocks/Z.png"
};

Easy_Asset_t* assets[sizeof(assetsOrigin)/sizeof(char*)];


bool loadingAssets(){
    int len = sizeof(assets)/sizeof(Easy_Asset_t*);
    for(int i = 0 ; i < len; i++){
        assets[i] = loadAsset(assetsOrigin[i]);
        if(assets[i] == NULL){
            cerr<<"Failed to load assets located at "<<assetsOrigin[i]<<endl;
        }
    }
    Easy_Asset_t* I = loadAsset("assets/blocks/I.png");
    Easy_Asset_t* J = loadAsset("assets/blocks/I.png");


    if ( I != J ){
        cout<<"Duplicate loading of same assets"<<endl;
        exit(-1);
    }

    return true;
}

typedef struct Player_Data {
    int x;
    int y;
    int rotation;
    Easy_Asset_t* piece;
    int assetIdx;
} Player_Data_t;

Player_Data_t playerOne = {
        .x = EASY_SDL_DEFAULT_WINDOW_WIDTH / 2,
        .y = EASY_SDL_DEFAULT_WINDOW_HEIGHT / 2,
        .rotation = 0,
        .piece = NULL,
        .assetIdx = 0
};

bool init(){
    loadingAssets();
    int len = sizeof(assets)/sizeof(Easy_Asset_t*);
    for(int i = 0 ; i < len && playerOne.piece == NULL; i++){
        if(assets[i]!=NULL){
            playerOne.assetIdx = i;
            playerOne.piece = assets[i];
            Image_Asset* img = &(playerOne.piece->detail.image);
            //PlayerOne is initialized as the center of the window
            //with this line I am going to center the Assets in the
            //center of the window
            playerOne.y -= img->height/2;
            playerOne.x -= img->width/2;
        }
    }
    return true;
}

bool loop() {

    SDL_Event e;
    while( true ) {
        if ( SDL_PollEvent( &e ) == 0 ) {
            SDL_Delay(10);
            continue;
        }
        switch (e.type) {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                break;
            case SDL_KEYUP:
                break;
            case SDL_MOUSEMOTION:
                break;
        }
        drawAsset(playerOne.x, playerOne.y,playerOne.piece, playerOne.rotation);
        SDL_RenderPresent(getSDLRender());
        SDL_Delay(10);
    }

    return true;
}

int main(int argc,char* argv[]){
    initEasySDL();
    init();
    loop();
    freeEasySDL();
}


