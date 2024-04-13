//Using SDL and standard IO
#define SDL_MAIN_HANDLED //avoid  "undefined reference to 'WinMain'"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "include/easy_sdl.h"
#include "include/tetris.h"


using namespace std;

static int cx = 0;
static int cy = 0;
static unsigned int idxBlock = 0;
static int angle = 0;

static int score = 0;

static int SPRITE_WIDTH = 256;
static int SPRITE_HEIGHT = 256;

static const float fallSpeed = 50;

//TODO Funzione che inizializza il mondo
typedef struct Player_Data {
    int x;
    int y;
    int rotation;
    Easy_Asset_t* piece;
    int assetIdx;
} Player_Data_t;

typedef struct World_Data {
    int points = 0;
    int topScore = 0;
    int level = 1;
    int nextBlock  = -1;
    const float fallSpeed = 50;
} World_Data_t;

static char world[WORLD_HEIGHT][WORLD_WIDTH];

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 938;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
TTF_Font* fontRules = NULL;
SDL_Texture* backgroundTexture = NULL;

const int MENU_OPTIONS_COUNT = 3;
const string MENU_OPTIONS[MENU_OPTIONS_COUNT] = {"Start Game", "Resume", "Quit"};

int selectedOption = 0;

void menu(SDL_Event*);
void game(SDL_Event*);

bool loadAssets(SDL_Renderer* render);
void (*gestore_eventi)(SDL_Event *) = &menu;


//TODO Compleate questo elenco con TUTTI gli assets che useremo
//IMPORTANTE: dare un ordine fisso agli assets
char* assetsOrigin[]  = {
    "assets/fonts/ka1.ttf",
    "assets/blocchi/arancione.png",
    "assets/blocchi/blu.png",
    "assets/blocchi/giallo.png",
    "assets/blocchi/rosa.png",
    "assets/blocchi/rosso.png",
    "assets/blocchi/verde.png",
    "assets/blocchi/viola.png",
    "assets/grafica/pausa1.png",
};

Easy_Asset_t* assets[sizeof(assetsOrigin)/sizeof(char*)];



bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL initialization failed: " << SDL_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow(
                              "Tetris - 3AI",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window == NULL) {
        cout << "Window creation failed: " << SDL_GetError() << endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cout << "Renderer creation failed: " << SDL_GetError() << endl;
        return false;
    }

    if (TTF_Init() == -1) {
        cout << "SDL_ttf initialization failed: " << TTF_GetError() << endl;
        return false;
    }

    font = TTF_OpenFont("assets/fonts/ka1.ttf", 42);
    fontRules = TTF_OpenFont("assets/fonts/Noteworthy.ttc", 48);

    if(fontRules == NULL) {
        cout << "Font loading failded: " << TTF_GetError() << endl;
        return false;
    }

    if (font == NULL) {
        cout << "Font loading failed: " << TTF_GetError() << endl;
        return false;
    }

    return true;
}

void closeSDL() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture(const string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == NULL) {
        cout << "Unable to load image " << filePath << ". Error: " << IMG_GetError() << endl;
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void renderText(const string& text, int x, int y, bool selected = false) {
    SDL_Color color = {255, 255, 255};
    if (selected) {
        color = {255, 0, 0};
    }
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int width = surface->w;
    int height = surface->h;
    SDL_FreeSurface(surface);

    SDL_Rect destRect = {x - width / 2, y - height / 2, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    SDL_DestroyTexture(texture);
}

void drawMenu() {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the background image
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);


    // Draw menu options
    int startY = (SCREEN_HEIGHT - MENU_OPTIONS_COUNT ) / 2;
    for (int i = 0; i < MENU_OPTIONS_COUNT; ++i) {
        int x = SCREEN_WIDTH / 2;
        int y = startY + i * 100;
        bool isSelected = (i == selectedOption);
        renderText(MENU_OPTIONS[i], x, y, isSelected);
    }

    // Update the screen
    SDL_RenderPresent(renderer);
}



void handleInput() {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT){
            closeSDL();
            exit(0);
        }else{
            gestore_eventi(&e);
        }
    }
}

void game(SDL_Event* e){
    cout << "Test game" << endl;
    gestore_eventi = &menu;
}


void menu(SDL_Event* e){
    if (e->type == SDL_QUIT) {
        closeSDL();
        exit(0);
    } else if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            case SDLK_UP:
                selectedOption = (selectedOption - 1 + MENU_OPTIONS_COUNT) % MENU_OPTIONS_COUNT;
                break;
            case SDLK_w:
                selectedOption = (selectedOption - 1 + MENU_OPTIONS_COUNT) % MENU_OPTIONS_COUNT;
                break;
            case SDLK_s:
                 selectedOption = (selectedOption + 1) % MENU_OPTIONS_COUNT;
                break;
            case SDLK_DOWN:
                selectedOption = (selectedOption + 1) % MENU_OPTIONS_COUNT;
                break;
            case SDLK_RETURN:
                switch (selectedOption) {
                    case 0:
                        cout << "Starting the game..." << endl;
                        gestore_eventi = &game;
                        break;
                    case 1:
                        cout << "Resume menu..." << endl;
                        gestore_eventi = &menu;
                        break;
                    case 2:
                        exit(0);
                        break;
                    default:

                        break;
                }
                break;
        }
    }
}


int main(int argc, char** args) {


    if (!initSDL()) {
        cout << "SDL initialization failed!" << endl;
        return 1;
    }

    backgroundTexture = loadTexture("assets/grafica/pausa_new_1.png");
    if (backgroundTexture == NULL) {
        closeSDL();
        return 1;
    }

    bool quit = false;

    while (!quit) {
        handleInput();
        drawMenu();
        SDL_Delay(10);
    }

    closeSDL();
    return 0;
}
