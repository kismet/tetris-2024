//Using SDL and standard IO
#include "../include/easy_sdl.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;

typedef struct Easy_SDL_Context {
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
    bool subsystem_sdl_loaded = false;
    bool subsystem_image_loaded = false;
    bool subsystem_ttf_loaded = false;
    uint16_t n_assets = 0;
    uint16_t max_assets = 0;
    Easy_Asset_t* assets = NULL;
} Easy_SDL_Context_t;

static Easy_SDL_Context_t context;


SDL_Window* getSDLWindow(){
    return context.window;
}

SDL_Renderer* getSDLRender() {
    return context.renderer;
}

bool freeEasySDL() {
    if (!(context.subsystem_sdl_loaded
        || context.subsystem_image_loaded
        || context.subsystem_ttf_loaded ) ) {
        return true;
    }
    if ( context.renderer != NULL ) {
        //TODO Check error cleaning
        SDL_RenderClear( context.renderer );
    }
    if ( context.window != NULL ) {
        //TODO Check error cleaning
        SDL_DestroyWindow( context.window );
    }
    //TODO delete all the loaded asssets

    if (context.subsystem_ttf_loaded) {
        //TODO Check error cleaning
        TTF_Quit();
    }
    if (context.subsystem_image_loaded) {
        //TODO Check error cleaning
        IMG_Quit();
    }
    if (context.subsystem_sdl_loaded) {
        //TODO Check error cleaning
        SDL_Quit();
    }
    return true;
}
bool initEasySDL( ) {
    return initEasySDL("EasySDL",
                       (int) EASY_SDL_DEFAULT_WINDOW_HEIGHT,
                       (int) EASY_SDL_DEFAULT_WINDOW_WIDTH,
                       (uint32_t) EASY_SDL_DEFAULT_WINDOW_OPTIONS
    );
}


bool initEasySDL(char* title, int width, int height, uint32_t options ){
    if ( context.subsystem_sdl_loaded ){
        return context.subsystem_sdl_loaded;
    }
    //TODO Free SDL, TTF, and IMG on failure
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        cerr<< "Error initializing SDL: " << SDL_GetError() << endl;
        return false;
    } else {
        context.subsystem_sdl_loaded = true;
    }

    if ( TTF_Init() < 0 ){
        cerr << "Error initializing TTF Failed: " << TTF_GetError() << endl;
        return false;
    } else {
        context.subsystem_ttf_loaded = true;
    }

    if ( IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0 ) {
        cerr << "Error initializing SDL Image: " << IMG_GetError() << endl;
        return false;
    } else {
        context.subsystem_image_loaded = true;
    }
    SDL_Window* w = NULL;
    if (options == 0 )  {
        w = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   height, width, SDL_WINDOW_RESIZABLE );
    }else{
        w = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   height, width, options );
    }
    if ( !w ) {
        cerr << "Error creating window: " << SDL_GetError()  << endl;
        return false;
    }else{
        context.window = w;
    }

    SDL_Renderer* r = NULL;
    r = SDL_CreateRenderer( w, -1 , SDL_RENDERER_ACCELERATED );
    if ( !r ) {
        cerr << "Error getting renderer: " << SDL_GetError() << endl;
        return false;
    }else{
        context.renderer =  r;
    }
    if (context.subsystem_sdl_loaded
    && context.subsystem_image_loaded
    && context.subsystem_ttf_loaded ) {
        context.max_assets = EASY_SDL_DEFAULT_ASSET_SLOT;
        context.assets = (Easy_Asset_t*) malloc(sizeof(Easy_Asset_t)*context.max_assets);
        context.n_assets = 0;
        return true;
    }else{
        //TODO Clean partial loaded SDL
        return false;
    }
}

Easy_Asset_t* getAssetById(uint16_t id){
    if(id >= context.n_assets )
        return NULL;

    return &(context.assets[id]);
}

Easy_Asset_t* loadAsset(char* path){
    Easy_Asset_t* t = loadImage(path);
    if (t != NULL) return t;
    t = loadFont(path);
    return t;
}


Easy_Asset_t* loadFont(char* path){
    return NULL;
}

int findAssetByName(char* path){
    for(int i=0;i<context.n_assets;i++){
        if(strcmp(path,context.assets[i].origin) == 0)
            return i;

    }
    return -1;
}

Easy_Asset_t* loadImage(char* path){
    if ( context.renderer == NULL ) {
        cerr << "No valid render. Assets cannot be loaded! Please invoke ??? first" << endl;
        return NULL;
    }

    int idx = findAssetByName(path);
    if( idx != -1){
        return &(context.assets[idx]);
    }

    if( context.n_assets == context.max_assets ){
        //TODO increase number of assets
        cerr<<"No more space for loading assets. Dynamic assets memories will fixed in next release"<<endl;
        return NULL;
    }


    Easy_Asset_t* asset = &context.assets[context.n_assets];

    SDL_Surface* image = IMG_Load(path);
    if(!image){
        cerr<<"Unable to load "<<path
            <<" Please check that file exits."<<endl
            <<"SDL says:"<<SDL_GetError()<<endl<<endl;
        return NULL;
    }
    asset->detail.image.surface = image;
    asset->detail.image.height = image->h;
    asset->detail.image.width = image->w;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(
            context.renderer, image );
    if(!texture){
        cerr<<"Unable to create texture "<<path<<" "<<SDL_GetError();
        return NULL;
    }
    asset->loaded = true;
    asset->detail.image.texture = texture;
    asset->type = ASSET_IMAGE;
    asset->id = context.n_assets;
    asset->origin = (char *) malloc(strlen(path));
    strcpy(asset->origin,path);
    context.n_assets++;
    //TODO init name
    return asset;
}

void drawAsset(uint16_t x, uint16_t y, Easy_Asset_t* asset,
               uint16_t rotation, float scaling){

    if ( asset->type != ASSET_IMAGE )
        return;
    SDL_Rect rect;
    rect.w = asset->detail.image.width;
    rect.h = asset->detail.image.height;
    rect.x = x;
    rect.y = y;

    SDL_RenderCopyEx(
        context.renderer,
        asset->detail.image.texture,
        NULL, &rect,
        rotation, NULL,
        SDL_FLIP_NONE);
}

void drawAsset(uint16_t x, uint16_t y, Easy_Asset_t* asset, uint16_t rotation){
    drawAsset(x,y,asset,rotation,1.0);
}

void drawAsset(uint16_t x, uint16_t y, Easy_Asset_t* asset){
    drawAsset(x,y,asset,0,1.0);
}

