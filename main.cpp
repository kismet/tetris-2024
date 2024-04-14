//Using SDL and standard IO
#define SDL_MAIN_HANDLED //avoid  "undefined reference to 'WinMain'"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "include/easy_sdl.h"
#include "include/tetris.h"


using namespace std;


static int MaxFallSpeed = 1000;

TextStyle_t normal = {
        .solid = true,
        .size = 42,
        .italic = false,
        .underline = false,
        .bold = false,
        .strikethrough = false,
        .font = NULL,
        .foreground = {255, 255,255, 255}
};

TextStyle_t highlight = {
        .solid = true,
        .size = 42,
        .italic = false,
        .underline = false,
        .bold = false,
        .strikethrough = false,
        .font = NULL,
        .foreground = {255, 0,0, 255}
};

typedef struct Player_Data {
    int x;
    int y;
    int rotation;
    Easy_Asset_t* piece;
    int assetIdx;
    int score = 0;
} Player_Data_t;

typedef struct World_Data {
    int points = 0;
    int topScore = 0;
    int level = 1;
    int nextBlock  = -1;
    int fallSpeed = 50;

} World_Data_t;

static char world[WORLD_HEIGHT][WORLD_WIDTH];

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 938;

const int MENU_OPTIONS_COUNT = 3;
char* MENU_OPTIONS[MENU_OPTIONS_COUNT] = {"Start Game", "Resume", "Quit"};

int selectedOption = 0;

void menu(SDL_Event*);
void game(SDL_Event*);

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
    "assets/grafica/pausa_new_1.png",
};

Easy_Asset_t* assets[sizeof(assetsOrigin)/sizeof(char*)];


void drawMenu() {
    // Clear the screen
    SDL_Renderer *renderer = getSDLRender();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the background image
    Easy_Asset_t *asset = loadAsset("assets/grafica/pausa_new_1.png");
    drawAsset(0,0, asset);

    // Draw menu options
    int startY = (SCREEN_HEIGHT - MENU_OPTIONS_COUNT ) / 2;
    for (int i = 0; i < MENU_OPTIONS_COUNT; ++i) {
        int x = SCREEN_WIDTH / 2;
        int y = startY + i * 100;
        bool isSelected = (i == selectedOption);
        if(isSelected){
            setTextStyle(&highlight);
        }else{
            setTextStyle(&normal);
        }
        drawText(
                (uint16_t ) x,(uint16_t ) y,
                (uint16_t ) SCREEN_WIDTH, (uint16_t ) 50,
                MENU_OPTIONS[i], TEXT_CENTERED
        );
    }

    // Update the screen
    SDL_RenderPresent(renderer);
}



void handleInput() {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT){
            freeEasySDL();
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
        freeEasySDL();
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
    bool quit = false;

    initEasySDL("Tetris 2024", SCREEN_WIDTH , SCREEN_HEIGHT,
                (uint32_t) EASY_SDL_DEFAULT_WINDOW_OPTIONS);
    normal.font = loadAsset("assets/fonts/ka1.ttf");
    highlight.font = normal.font;
    gestore_eventi =  &menu;

    while (!quit) {
        handleInput();
        drawMenu();
        SDL_Delay(10);
    }

}
