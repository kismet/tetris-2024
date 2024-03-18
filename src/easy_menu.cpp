#define SDL_MAIN_HANDLED // avoid  "undefined reference to 'WinMain'"

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "../include/tetris_asset.h"
#include "../include/easy_sdl.h"

using namespace std;

/**
 * Qui carico l'elenco dei font che voglio usare i font devono
 * essere al percorso locale
 */
char* assetsOrigin[] = {
        "assets/fonts/ka1.ttf"
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

    TextStyle_t style = {
            .solid = true,
            .size = 18,
            .italic = false,
            .underline = false,
            .bold = false,
            .strikethrough = false,
            .font = assets[0],
            .foreground = {255, 255,255, 255}
    };
    setTextStyle(&style);
    return true;
}
/**
 * Questa parte di codice definisce i vari gestori degli eventi
 * in base allo "Stato" del gioco.
 * Per cambiare stato devo solo aggiornare la variabile
 *      gestore_eventi
 * assegnandogli il gestore attivo per quell'evento
 */
void menu(SDL_Event* );
void game(SDL_Event* );

void (*gestore_eventi)(SDL_Event *) = &menu;

bool loop(){
    SDL_Event e;
    while( true ) {
        if ( SDL_PollEvent( &e ) == 0 ) {
            SDL_Delay(10);
            continue;
        }
        switch (e.type) {
            case SDL_QUIT:
                return false;
                break;
            default:
                gestore_eventi(&e);
            break;
        }
        //Questo è un esempio per come stampare a video del testo
        drawText(
                0,100,
                EASY_SDL_DEFAULT_WINDOW_WIDTH, 100,
                "Testo Centrato", TEXT_CENTERED
        );
        SDL_RenderPresent(getSDLRender());
        SDL_Delay(10);
    }

    return true;
}

void game(SDL_Event* event){
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                        gestore_eventi = &menu;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void menu(SDL_Event* event){
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

int main(int argc,char* argv[]){
    initEasySDL();
    loadingAssets();
    loop();
    freeEasySDL();
}


