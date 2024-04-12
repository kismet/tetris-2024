#define SDL_MAIN_HANDLED // avoid  "undefined reference to 'WinMain'"

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "../include/tetris_asset.h"
#include "../include/easy_sdl.h"

using namespace std;

char* assetsOrigin[] = {
        "assets/fonts/ka1.ttf"
};

TextStyle_t normal = {
        .solid = true,
        .size = 44,
        .italic = false,
        .underline = false,
        .bold = false,
        .strikethrough = false,
        .font = NULL,
        .foreground = {255, 0,255, 255}
};

TextStyle_t highlight = {
        .solid = true,
        .size = 44,
        .italic = false,
        .underline = false,
        .bold = false,
        .strikethrough = false,
        .font = NULL,
        .foreground = {255, 0,255, 255}
};

TextStyle_t gametext = {
        .solid = true,
        .size = 12,
        .italic = false,
        .underline = false,
        .bold = false,
        .strikethrough = false,
        .font = NULL,
        .foreground = {255, 0,255, 255}
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
    normal.font = assets[0];
    highlight.font = assets[0];
    gametext.font = assets[0];

    setTextStyle(&normal);
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
        drawText(playerOne.x+50,playerOne.y+50, "Funziona!");
        /*
        drawText(
                0,0,
                EASY_SDL_DEFAULT_WINDOW_HEIGHT, EASY_SDL_DEFAULT_WINDOW_WIDTH,
                "Testo Centrato", TEXT_CENTERED
        ); */
        drawText(
                0,0,
                EASY_SDL_DEFAULT_WINDOW_WIDTH, EASY_SDL_DEFAULT_WINDOW_HEIGHT,
                "Testo Centrato", TEXT_CENTERED
        );
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


