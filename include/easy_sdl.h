#ifndef EASY_SDL_H
#define EASY_SDL_H

#include <SDL.h>

#define EASY_SDL_DEFAULT_ASSET_SLOT 50
#define EASY_SDL_DEFAULT_WINDOW_HEIGHT 768
#define EASY_SDL_DEFAULT_WINDOW_WIDTH 1366
#define EASY_SDL_DEFAULT_WINDOW_OPTIONS SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN


typedef struct Image_Asset {
    uint16_t height;
    uint16_t width;
    SDL_Texture* texture;
    SDL_Surface* surface;
} Image_Asset_t;

typedef struct Font_Asset {
    bool placeholder;
} Font_Asset_t;

typedef enum Asset_Type{
    ASSET_IMAGE, ASSET_FONT
} Asset_Type_t;

typedef union Easy_Asset_Union {
    Image_Asset_t image;
    Font_Asset_t font;
} Easy_Asset_Union_t;


typedef struct Easy_Asset {
    Asset_Type_t type;
    uint32_t id;
    bool loaded;
    char* origin;
    char* name;
    Easy_Asset_Union_t detail;
} Easy_Asset_t;

/**
 * This is the <b>FIRST</b> that must invoked by the developers
 * for creating a proper context, otherwise all the other function
 * will fail
 * By default this crate a FRAMED window with Hardware acceleration
 * enabled, moreover this function will load all the SDL most common
 * SDL subsystem (Core, Image, and Font)
 *
 * @param title The title to assign to the widow
 * @param width Width of the window
 * @param height Height of the window
 * @param options other options to pass to SDL please refers to #SDL_init()
 * @return TRUE if and only if the initialization succeeded
 */
bool initEasySDL(char* title, int width, int height, uint32_t options );

/**
 * This load a 800x600 windows with "Easy SDL" as title
 * by invoking the initEasySDL function
 *
 * @see initEasySDL
 */
bool initEasySDL();

bool freeEasySDL();

// TODO lazy loading assest
// Easy_Asset_t* addAsset(char* path);

Easy_Asset_t* loadAsset(char* path);

/**
 * This function returns a loaded Asset (eventually it will try to load it)
 *
 * @param id the id that represents the asset to require
 * @return the Asset matching the id or NULL if none is found
 */
Easy_Asset_t* getAssetById(int id);

//
//Easy_Asset_t* getAssetById(char* name);

/**
 * Load a Font as Assets and return it, otherwise it will delete
 *
 *
 * @param path
 * @return
 */
Easy_Asset_t* loadFont(char* path);

Easy_Asset_t* loadImage(char* path);

void drawAsset(uint16_t x, uint16_t y, SDL_Texture *asset, uint16_t rotation, float scaling);

void drawAsset(uint16_t x, uint16_t y, SDL_Texture *asset, uint16_t rotation);

void drawAsset(uint16_t x, uint16_t y, SDL_Texture *asset);

/**
 * The following section contains function that allows the developer
 * to access the SDL layer for using specific function that are not
 * exposed by the EasySDL layer
 */

/**
 *
 * @return
 */
SDL_Window* getSDLWindow();

SDL_Renderer* getSDLRender();


#endif //EASY_SDL_H
