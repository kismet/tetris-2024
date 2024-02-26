#ifndef EASY_SDL_H
#define EASY_SDL_H

#include <SDL.h>


SDL_Window* getSDLWindow();

SDL_Renderer* getSDLRender();

void drawAsset(uint16_t x, uint16_t y, SDL_Texture *asset, uint16_t rotation, float scaling);

void drawAsset(uint16_t x, uint16_t y, SDL_Texture *asset, uint16_t rotation);

void drawAsset(uint16_t x, uint16_t y, SDL_Texture *asset);

bool initEasySDL(char* title, uint16_t width, uint16_t height, uint16_t options );

#endif //EASY_SDL_H
