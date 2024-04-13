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

static const float fallSpeed = 50;

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
char* MENU_OPTIONS[MENU_OPTIONS_COUNT] = {"Start Game", "Resume", "Quit"};

int selectedOption = 0;

void menu(SDL_Event*);
void game(SDL_Event*);

bool loadAssets(SDL_Renderer* render);
void (*gestore_eventi)(SDL_Event *) = &menu;


char* FONT_PATH = "assets/fonts/ka1.ttf";
char* IMAGE_MENU_BACKGROUND = ""; //TODO Set the right path;
char* IMAGE_GAME_BACKGROUND = ""; //TODO Set the right path;

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
    "assets/grafica/pausa_new_1.png"
};
const int N_ASSETS = sizeof(assetsOrigin)/sizeof(char*);
Easy_Asset_t* assets[N_ASSETS];


void drawMenu() {
    /*
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the background image
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    */
    Easy_Asset_t *asset = NULL;
    cout<<"Loading assets"<<endl;
    //asset = loadAsset("assets/grafica/pausa_new_1.png");
    cout<<"Loaded assets"<<endl;
    drawAsset(0,0, asset);
    cout<<"Drawn assets"<<endl;
    return;

    // Draw menu options
    int startY = (SCREEN_HEIGHT - MENU_OPTIONS_COUNT ) / 2;
    for (int i = 0; i < MENU_OPTIONS_COUNT; ++i) {
        int x = SCREEN_WIDTH / 2;
        int y = startY + i * 100;
        bool isSelected = (i == selectedOption);
        drawText(
                (uint16_t ) x,(uint16_t ) y,
                (uint16_t ) SCREEN_WIDTH, (uint16_t ) 50,
                MENU_OPTIONS[i], TEXT_CENTERED
        );
        //renderText(MENU_OPTIONS[i], x, y, isSelected);
    }

    // Update the screen
    //SDL_RenderPresent(renderer);
}



void handleInput() {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT){
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


bool loadingAssets() {
    int len = sizeof(assets) / sizeof(Easy_Asset_t *);
    for (int i = 0; i < len; i++) {
        cout<<"Loading: "<<assetsOrigin[i]<<endl;
        assets[i] = loadAsset(assetsOrigin[i]);
        if (assets[i] == NULL) {
            cerr << "Failed to load assets located at " << assetsOrigin[i] << endl;
            cerr << "We have to close down the software " << endl;
            exit(-1);
        }
    }
    //normal.font = loadAsset(FONT_PATH);
    //highlight.font = loadAsset(FONT_PATH);

}



int main(int argc, char** args) {
    //1 - Creiamo l'ambiente
    initEasySDL("Tetris 2024", SCREEN_WIDTH, SCREEN_HEIGHT,NULL);
    loadingAssets();
    cout<<"Loading completed"<<endl;

    while ( true ) {
        handleInput();
        drawMenu();
        SDL_Delay(1000);
    }

    return 0;
}
