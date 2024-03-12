//Using SDL and standard IO
#include "../include/easy_sdl.h"
#include "../include/tetris_asset.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
using namespace std;

static unsigned int n_images = 0;

static t_image images[] = {
    {
        false, "assets/blocks/I.png", NULL, 64, 64*4
    },
    {
        false, "assets/blocks/J.png", NULL, 64*3, 64*2

    },
    {
        false, "assets/blocks/L.png", NULL, 64*3, 64*2

    },
    {
        false, "assets/blocks/O.png", NULL, 64*2, 64*2

    },
    {
        false, "assets/blocks/S.png", NULL, 64*4, 64*2

    },
    {
        false, "assets/blocks/T.png", NULL, 64*3, 64*2

    },
    {
        false, "assets/blocks/Z.png", NULL, 64*3, 64*2

    }
};

t_image* getAssets(){
    return images;
}

unsigned int getNAssets(){
    return n_images;
}


bool loadAssets(SDL_Renderer* render){
    if( render == NULL ) {
        render = getSDLRender();
    }
    if( render == NULL ){
        //TODO handle wrong invokation order
        cerr<<"No valid render. Assets cannot be loaded! Please invoke ??? first"<<endl;
    }
    int n = sizeof(images)/sizeof(t_image);
    bool flag = true;
    for(int i=0; i<n;i++){
        SDL_Texture* block = IMG_LoadTexture(render, images[i].origin);
        if(!block){
            cerr<<"Failed to load "<<images[i].origin<<endl;
            images[i].loaded = false;
            flag = false;
            continue;
        }
        cout<<"Loaded "<<images[i].origin<<endl;
        images[i].loaded = true;
        images[i].texture = block;
        n_images++;
    }
    return true;
}

