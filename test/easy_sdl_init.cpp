
#define SDL_MAIN_HANDLED // avoid  "undefined reference to 'WinMain'"

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "../include/tetris_asset.h"
#include "../include/easy_sdl.h"

using namespace std;





bool loop() {

    SDL_Event e;
    uint64_t loops = 0;
    while( true ) {
        if ( SDL_PollEvent( &e ) == 0 ) {
            SDL_Delay(10);
            continue;
        }
        switch (e.type) {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                cout<<"KeyDown:"<<e.key.keysym.sym;
                break;
            case SDL_KEYUP:
                cout<<"KeyUp:"<<e.key.keysym.sym;
                break;
            case SDL_MOUSEMOTION:
                break;
        }
        SDL_RenderPresent(getSDLRender());
        SDL_Delay(10);
        cout<<loops<<" ";
        loops++;
        if( loops % 20 == 0 ) cout<<endl;
    }

    return true;
}

int main(int argc,char* argv[]){
    initEasySDL();
    loop();
    freeEasySDL();
}


