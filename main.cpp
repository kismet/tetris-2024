//Using SDL and standard IO
#define SDL_MAIN_HANDLED //avoid  "undefined reference to 'WinMain'"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <random>
#include <ctime>
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

TextStyle_t info = {
    .solid = true,
    .size = 40,
    .italic = false,
    .underline = false,
    .bold = true,
    .strikethrough = false,
    .font = NULL,
    .foreground = {255, 255, 255, 255}
};

typedef struct Player_Data {
    int x;
    int y;
    int rotation;
    Easy_Asset_t* piece;
    int assetIdx;
    int score = 0;
} Player_Data_t;

Player_Data_t playerOne;

typedef struct World_Data {
    int points = 0;
    int topScore = 0;
    int level = 1;
    int nextBlock  = -1;
    int fallSpeed = 50;

} World_Data_t;

World_Data_t currentGame;

static char world[WORLD_HEIGHT][WORLD_WIDTH];

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 938;

const int MENU_OPTIONS_COUNT = 3;
char* MENU_OPTIONS[MENU_OPTIONS_COUNT] = {"Start Game","Resume", "Quit"}; //TODO Cambiare Resume con i Titoli di coda

const int PAUSE_OPTIONS_COUNT = 3;
char* PAUSE_OPTIONS[PAUSE_OPTIONS_COUNT] = {"New Game", "Resume", "Menu"};

int selectedOption = 0;

void menu(SDL_Event*);
void game(SDL_Event*);
void pause(SDL_Event*);

void (*gestore_eventi)(SDL_Event *) = &menu;


//TODO Compleate questo elenco con TUTTI gli assets che useremo
//IMPORTANTE: dare un ordine fisso agli assets
char* assetsOrigin[]  = {
    "assets/fonts/ka1.ttf",
    "assets/fonts/Monaco.ttf",
    "assets/blocchi/arancione.png",
    "assets/blocchi/blu.png",
    "assets/blocchi/giallo.png",
    "assets/blocchi/rosa.png",
    "assets/blocchi/rosso.png",
    "assets/blocchi/verde.png",
    "assets/blocchi/viola.png",
    "assets/grafica/pausa_new_1.png",
    "assets/grafica/game.png"
};

Easy_Asset_t* assets[sizeof(assetsOrigin)/sizeof(char*)];



void handleInput() {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT){
            freeEasySDL();
            exit(0);
        }else if (e.key.keysym.sym == SDLK_ESCAPE){
            gestore_eventi = &pause;
        }
        else {
            gestore_eventi(&e);
        }
    }
}



//TODO implement function for generating the index for the next block
int randIndex() {

    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(1, 7);

    return dis(gen);
}

//TODO implement function draw background
void drawBackground() {
    Easy_Asset_t *asset = loadAsset("assets/grafica/game.png");
    drawAsset(0,0, asset);
}

void drawInfo() {
   // setTextStyle(&info);

    const int N_INFO = 3;

    string topString = to_string(currentGame.topScore);
    string scoreString = to_string(playerOne.score);
    string levelString = to_string(currentGame.level);

    char* textInfo[N_INFO] = {&topString[0],&scoreString[0], &levelString[0]};


        int startSize = 1000;
        int startY = 190;
        int x = 235;

        int textSize = 10 + playerOne.score / 100;

        TextStyle_t textStyle = info;
        textStyle.size = textSize;
        setTextStyle(&textStyle);

        drawText(
                (uint16_t ) x,(uint16_t ) startY + 0 * 310,
                (uint16_t ) 35, (uint16_t ) 35,
                textInfo[0], TEXT_LEFT
                );
        drawText(
                (uint16_t ) (x-20) + (playerOne.score) / 2000,(uint16_t ) startY + 1 * 310,
                (uint16_t ) 75, (uint16_t ) 50,
                textInfo[1], TEXT_LEFT
                );
        drawText(
                (uint16_t ) x,(uint16_t ) startY + 2 * 305,
                (uint16_t ) 35, (uint16_t ) 35,
                textInfo[2], TEXT_LEFT
                );
}

void drawWorld() {

}
//TODO implement function draw player block
void drawPlayerBlock(Player_Data_t player) {

}

//TODO implement the game mode
void game(SDL_Event* e){
        cout << "Test game" << endl;
        // Clear the screen
        SDL_Renderer *renderer = getSDLRender();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

    //TODO drawbackground
        drawBackground();
    //TODO drawpoints and all the text info
        drawInfo();

    //TODO drawworld


    //TODO hanldeinput or handle fall speedkj
    //TODO check that after the call to placeIt we have to generate a new block
    //TODO draw the playerblock


    //Parte per il test del punteggio
        playerOne.score += 10;// per fare un test del resume, new game, aggiornamento punteggio

        int targetScore = currentGame.level * 3000;

        if(playerOne.score >= targetScore) {
            //TODO verificare se la velocita e' adeguata
            currentGame.level++;
        }

    SDL_RenderPresent(renderer);
}


void menu(SDL_Event* e){
    if (e->type == SDL_QUIT) {
        freeEasySDL();
        exit(0);
    } else if (e->type == SDL_KEYUP) {
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
                        //TODO inizializzare la matrice world[][] e tutte le variabili relative (punteggio, level, etc.)

                        playerOne.score = 0;
                        currentGame.level = 0;
                        gestore_eventi = &game;
                        break;
                    case 1:
                        cout << "Resume game..." << endl;
                        gestore_eventi = &game;
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

void drawMenu() {
    // Clear the screen
    SDL_Renderer *renderer = getSDLRender();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the background image
    Easy_Asset_t *asset = loadAsset("assets/grafica/menu.png");
    drawAsset(0,0, asset);

    normal.size = 42;
    highlight.size = 42;

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


void pause(SDL_Event* e){
    if (e->type == SDL_QUIT) {
        freeEasySDL();
        exit(0);
    } else if (e->type == SDL_KEYUP) {
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
                        cout << "Starting new game..." << endl;
                        //TODO inizializzare la matrice world[][] e tutte le variabili relative (punteggio, level, etc.)

                        playerOne.score = 0;
                        currentGame.level = 0;
                        gestore_eventi = &game;
                        break;
                    case 1:
                        cout << "Resume game..." << endl;
                        gestore_eventi = &game;
                        break;
                    case 2:
                        cout << "Menu..." << endl;
                        gestore_eventi = &menu;
                        break;
                    default:

                        break;
                }
                break;
        }
    }
}

void drawPause() {
    // Clear the screen
    SDL_Renderer *renderer = getSDLRender();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the background image
    Easy_Asset_t *asset = loadAsset("assets/grafica/pausa.png");
    drawAsset(0,0, asset);

    normal.size = 58;
    highlight.size = 58;

    // Draw menu options
    int startY = (SCREEN_HEIGHT - PAUSE_OPTIONS_COUNT ) / 3;
    for (int i = 0; i < PAUSE_OPTIONS_COUNT; ++i) {
        int x = SCREEN_WIDTH / 2;
        int y = startY + i * 150;
        bool isSelected = (i == selectedOption);
        if(isSelected){
            setTextStyle(&highlight);
        }else{
            setTextStyle(&normal);
        }
        drawText(
                (uint16_t ) x,(uint16_t ) y,
                (uint16_t ) SCREEN_WIDTH, (uint16_t ) 60,
                PAUSE_OPTIONS[i], TEXT_CENTERED
        );
    }

    // Update the screen
    SDL_RenderPresent(renderer);
}


int main(int argc, char** args) {
    bool quit = false;

    initEasySDL("Tetris 2024", SCREEN_WIDTH , SCREEN_HEIGHT,
                (uint32_t) EASY_SDL_DEFAULT_WINDOW_OPTIONS);
    normal.font = loadAsset("assets/fonts/ka1.ttf");
    highlight.font = normal.font;
    info.font = loadAsset("assets/fonts/Monaco.ttf");
    gestore_eventi =  &menu;

    while (!quit) {
        handleInput();
        if(gestore_eventi == &menu){
            drawMenu();
        }
        if(gestore_eventi == &pause) {
            drawPause();
        }
        SDL_Delay(10);
    }

}
