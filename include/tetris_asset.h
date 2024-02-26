#ifndef TETRIS_ASSET_H
#define TETRIS_ASSET_H

typedef struct {
    bool loaded = false;
    char* origin;
    SDL_Texture* texture;
    int width;
    int height;
} t_image;

#ifndef TETRIS_ASSET_H_IMAGE
#define TETRIS_ASSET_H_IMAGE
#endif // TETRIS_ASSET_H_IMAGE

bool loadAssets(SDL_Renderer* render);

t_image* getAssets();

unsigned int getNAssets();

#endif // __TETRIS_ASSET__
