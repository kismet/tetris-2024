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

TextStyle_t score = {
        .solid = true,
        .size = 10,
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
        .foreground = {255, 255,0, 255}
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

TextStyle_t game_over = {
    .solid = true,
    .size = 40,
    .italic = false,
    .underline = false,
    .bold = false,
    .strikethrough = false,
    .font = NULL,
    .foreground = {0, 0, 0, 255}
};


Player_Data_t playerOne;

World_Data_t currentGame;

static char world[WORLD_HEIGHT][WORLD_WIDTH];

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 938;

int nextRotation;
int nextY;
int nextX;

const int MENU_OPTIONS_COUNT = 3;
char* MENU_OPTIONS[MENU_OPTIONS_COUNT] = {"Start Game","Credits", "Quit"};


const int PAUSE_OPTIONS_COUNT = 3;
char* PAUSE_OPTIONS[PAUSE_OPTIONS_COUNT] = {"New Game", "Resume", "Menu"};

const int CREDITS_COUNT = 1;
char* CREDITS_OPTIONS[CREDITS_COUNT] = {"Menu"};

const int GAMEOVER_COUNT = 2;
char* GAMEOVER_OPTIONS[GAMEOVER_COUNT] = {"Menu", "Quit"};

int selectedOption = 0;

void menu(SDL_Event*);
void game(SDL_Event*);
void pause(SDL_Event*);
void credits(SDL_Event*);
void gameover(SDL_Event*);

void (*gestore_eventi)(SDL_Event *) = &menu;


//TODO Compleate questo elenco con TUTTI gli assets che useremo
//IMPORTANTE: dare un ordine fisso agli assets
char* assetsOrigin[]  = {
    "assets/blocchi/arancione.png",
    "assets/blocchi/blu.png",
    "assets/blocchi/giallo.png",
    "assets/blocchi/rosa.png",
    "assets/blocchi/rosso.png",
    "assets/blocchi/verde.png",
    "assets/blocchi/viola.png",
    "assets/grafica/menu.png",
    "assets/grafica/game.png",
    "assets/grafica/pausa.png",
    "assets/grafica/titoli_coda.png",
    "assets/fonts/ka1.ttf",
    "assets/fonts/Monaco.ttf",
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


void drawBackground() {
    Easy_Asset_t *asset = loadAsset("assets/grafica/game.png");
    drawAsset(0,0, asset);
}

void drawInfo(Player_Data_t player) {
    setTextStyle(&info);

    const int N_INFO = 3;

    string topString = to_string(currentGame.topScore);
    string scoreString = to_string(playerOne.score);
    string levelString = to_string(currentGame.level);

    char* textInfo[N_INFO] = {&topString[0],&scoreString[0], &levelString[0]};


        int startSize = 1000;
        int startY = 200;
        int x = 235;

        int nextBlockY = 460;
        int nextBlockX = 1095;

        if(playerOne.score > 0){
            int textSize = 15 * playerOne.score / 10 ;

            score.size = textSize;
            setTextStyle(&score);

            drawText(
                (uint16_t ) (x-10) + currentGame.topScore / 10000,(uint16_t ) startY,
                (uint16_t ) 50 + (currentGame.topScore) / 800, (uint16_t ) 50,
                textInfo[0], TEXT_LEFT
                );
        drawText(
                (uint16_t ) (x-10) + (playerOne.score) / 10000 ,(uint16_t ) startY + 1 * 330,
                (uint16_t ) 50 + (playerOne.score) / 800, (uint16_t ) 50,
                textInfo[1], TEXT_LEFT
                );
        drawText(
                (uint16_t ) x,(uint16_t ) startY + 2 * 305,
                (uint16_t ) 35, (uint16_t ) 35,
                textInfo[2], TEXT_LEFT
                );
        }
        else if (playerOne.score == 0){
            drawText(
                (uint16_t ) x,(uint16_t ) startY,
                (uint16_t ) 50, (uint16_t ) 50,
                textInfo[0], TEXT_LEFT
                );
        drawText(
                (uint16_t ) x,(uint16_t ) startY + 1 * 330,
                (uint16_t ) 50, (uint16_t ) 50,
                textInfo[1], TEXT_LEFT
                );
        drawText(
                (uint16_t ) x,(uint16_t ) startY + 2 * 305,
                (uint16_t ) 35, (uint16_t ) 35,
                textInfo[2], TEXT_LEFT
                );
        }

        const int NO_ROTATION = 0;
        for(int i = 0; i < SHAPE_HEIGHT; i++){
            for(int j = 0; j < SHAPE_WIDTH; j++){
                char point = blocks[currentGame.nextBlock][NO_ROTATION][i][j];
            if(point != ' '){
                Easy_Asset_t *block = loadAsset(assetsOrigin[point - '1']);
                drawAsset(
                          nextBlockX + j * 32,
                          nextBlockY + i * 32,
                          block
                          );
            }
        }
    }
}

void drawWorld() {
    for(int i = 0; i < WORLD_HEIGHT; i++){
        for(int j = 0; j < WORLD_WIDTH; j++) {
            if(world[i][j]  >= '1' && world[i][j] <= '7'){
                Easy_Asset_t *block = loadAsset(assetsOrigin[world[i][j] - '1']);
                drawAsset(
                          540 + j * 32,
                          i * 32,
                          block
                          );
            }
        }
    }
}

void drawPlayerBlock(Player_Data_t player) {
    for(int i = 0; i < SHAPE_HEIGHT; i++){
        for(int j = 0; j < SHAPE_WIDTH; j++){
                char point = blocks[player.assetIdx][player.rotation][i][j];
            if(point != ' '){
                Easy_Asset_t *block = loadAsset(assetsOrigin[point - '1']);
                drawAsset(
                          540 + (j +player.x) * 32,
                          (i + player.y) * 32,
                          block
                          );
            }
        }
    }
}

void newBlock(Player_Data_t& playerOne, World_Data_t& currentGame){
        playerOne.y = 0;
        playerOne.x = 3;
        playerOne.assetIdx = currentGame.nextBlock;
        currentGame.nextBlock = randIndex();
}

void drawGame(){
    //TODO Avoid to render multiple time info and block if nothing happened
         // Clear the screen
            SDL_Renderer *renderer = getSDLRender();
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            drawBackground();

            drawInfo(playerOne);

            drawWorld();

            drawPlayerBlock(playerOne);

            int currentTime = SDL_GetTicks();
            int s = currentTime - currentGame.lastTime;

            upgradeLevel(playerOne, currentGame);
             if(gameOver(playerOne, currentGame, blocks, world)){
                            cout << "Game Over.." << endl;
                            gestore_eventi = &gameover;
                }

            if (s >= currentGame.fallSpeed) {
                    if (!isColliding(playerOne.y + 1, playerOne.x, playerOne.rotation,  playerOne, currentGame, blocks, world)) {
                        playerOne.y += 1;
                        currentGame.lastTime = currentTime;
                    }
                    else {
                        placeIt(playerOne, currentGame, blocks, world, playerOne.score);

                        if(playerOne.score > currentGame.topScore){
                            currentGame.topScore = playerOne.score;
                        }
                        newBlock(playerOne, currentGame);
                    }

            }

        SDL_RenderPresent(renderer);
}



void game(SDL_Event* e){

        if(e->type == SDL_QUIT){
            freeEasySDL();
            exit(0);
        }
        else if(e->type == SDL_KEYDOWN){
            switch(e->key.keysym.sym){
    case SDLK_s: case SDLK_DOWN:
                            nextY = playerOne.y + 1;
                            if (!isColliding(nextY, playerOne.x, playerOne.rotation, playerOne, currentGame, blocks, world)) {
                                playerOne.y = nextY;
                            }
                            break;
                    case SDLK_a: case SDLK_LEFT:
                            nextX = playerOne.x - 1;
                            if (!isColliding(playerOne.y, nextX, playerOne.rotation, playerOne, currentGame, blocks, world)) {
                            playerOne.x = nextX;
                            }
                            break;
                    case SDLK_d: case SDLK_RIGHT:
                           nextX  = playerOne.x +1;
                            if (!isColliding(playerOne.y, nextX, playerOne.rotation, playerOne, currentGame, blocks, world)) {
                            playerOne.x = nextX;
                            }
                            break;
                        case SDLK_q:
                            nextRotation = (playerOne.rotation - 1 + ROTATION) %ROTATION;
                            if (!isColliding(playerOne.y, playerOne.x, nextRotation,playerOne, currentGame, blocks, world)){
                                playerOne.rotation = nextRotation;
                            }
                            break;
                        case SDLK_e:
                            nextRotation = (playerOne.rotation + 1 + ROTATION)%ROTATION;
                             if (!isColliding(playerOne.y, playerOne.x, nextRotation, playerOne, currentGame, blocks, world)){
                                playerOne.rotation = nextRotation;
                             }
                            break;
                        case SDLK_UP:
                            nextRotation = (playerOne.rotation + 1 + ROTATION)%ROTATION;
                             if (!isColliding(playerOne.y, playerOne.x, nextRotation, playerOne, currentGame, blocks, world)){
                                playerOne.rotation = nextRotation;
                             }
                            break;
                        case SDLK_SPACE:
                            fallDown(playerOne, currentGame, blocks, world, playerOne.score);
                            newBlock(playerOne, currentGame);
                            break;
                    }
        }
}

void gameover(SDL_Event* e){
    if (e->type == SDL_QUIT) {
        freeEasySDL();
        exit(0);
    } else if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            case SDLK_LEFT:
                selectedOption = (selectedOption - 1 + GAMEOVER_COUNT) % GAMEOVER_COUNT;
                break;
            case SDLK_a:
                selectedOption = (selectedOption - 1 + GAMEOVER_COUNT) % GAMEOVER_COUNT;
                break;
            case SDLK_d:
                 selectedOption = (selectedOption + 1) % GAMEOVER_COUNT;
                break;
            case SDLK_RIGHT:
                selectedOption = (selectedOption + 1) % GAMEOVER_COUNT;
                break;
            case SDLK_RETURN:
                switch (selectedOption) {
                    case 0:
                        cout << "Back to menu..." << endl;
                        gestore_eventi = &menu;
                        break;
                    case 1:
                        cout << "Quit..." << endl;
                        exit(0);
                        break;
                }
                break;
        }
    }
}

void drawGameover(Player_Data_t player){

    const int G_INFO = 3;

    string topString = to_string(currentGame.topScore);
    string scoreString = to_string(playerOne.score);

    char* gameoverInfo[G_INFO] = {&topString[0],&scoreString[0]};

    // Clear the screen
    SDL_Renderer *renderer = getSDLRender();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    Easy_Asset_t *asset = loadAsset("assets/grafica/gameover.png");
    drawAsset(0,0, asset);

    normal.size = 42;
    highlight.size = 42;

    int startX = 345;
    for (int i = 0; i < GAMEOVER_COUNT; ++i) {
        int x = startX + i * 510;
        int y = 790;
        bool isSelected = (i == selectedOption);
        if(isSelected){
            setTextStyle(&highlight);
        }else{
            setTextStyle(&game_over);
        }
        drawText(
                (uint16_t ) x,(uint16_t ) y + i * -10,
                (uint16_t ) 200, (uint16_t ) 50,
                GAMEOVER_OPTIONS[i], TEXT_LEFT
        );
    }


    int pointStart = 340;
    for(int i = 0; i < GAMEOVER_COUNT; i++){
        int x = pointStart + i * 510;
        int y = 460;
        setTextStyle(&info);
        drawText(
                (uint16_t ) x,(uint16_t ) y,
                (uint16_t ) 200, (uint16_t ) 50,
                gameoverInfo[i], TEXT_LEFT
                );
    }



    // Update the screen
    SDL_RenderPresent(renderer);
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
                        //TODO inizializzare la matrice world[][] e tutte le variabili relative (punteggio, level, etc.)
                        setupNewGames(playerOne, currentGame, world);
                        gestore_eventi = &game;
                        break;
                    case 1:
                        cout << "Credits..." << endl;
                        gestore_eventi = &credits;
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
                        cout << "Starting new game..." << endl;
                        //TODO inizializzare la matrice world[][] e tutte le variabili relative (punteggio, level, etc.)
                        setupNewGames(playerOne, currentGame, world);
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

void credits(SDL_Event* e){
    if (e->type == SDL_QUIT) {
        freeEasySDL();
        exit(0);
    } else if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            case SDLK_RETURN:
                switch (selectedOption) {
                    case 0:
                        cout << "Back to menu..." << endl;
                        gestore_eventi = &menu;
                        break;
                }
                break;
        }
    }
}

void drawCredits(){
    // Clear the screen
    SDL_Renderer *renderer = getSDLRender();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the background image
    Easy_Asset_t *asset = loadAsset("assets/grafica/titoli_coda.png");
    drawAsset(0,0, asset);

    normal.size = 42;
    highlight.size = 42;

    selectedOption = 0;
    setTextStyle(&highlight);

    int y = (SCREEN_HEIGHT - CREDITS_COUNT ) / 2 + 300;
    int x = SCREEN_WIDTH / 2;

        drawText(
                (uint16_t ) x,(uint16_t ) y,
                (uint16_t ) SCREEN_WIDTH, (uint16_t ) 60,
                CREDITS_OPTIONS[0], TEXT_CENTERED
        );

    // Update the screen
    SDL_RenderPresent(renderer);
}

/*
bool precachingAssets(){
    int len = sizeof(assets)/sizeof(Easy_Asset_t*);
    for(int i = 0 ; i < len; i++){
        assets[i] = loadAsset(assetsOrigin[i]);
        if(assets[i] == NULL){
            cerr<<"Failed to load assets located at "<<assetsOrigin[i]<<endl;
            return false;
        }
    }
    return true;
}
*/

int main(int argc, char** args) {
    bool quit = false;

    initEasySDL("Tetris 2024", SCREEN_WIDTH , SCREEN_HEIGHT,
                (uint32_t) EASY_SDL_DEFAULT_WINDOW_OPTIONS | SDL_WINDOW_BORDERLESS);
   /* if ( precachingAssets() == false ) {
        freeEasySDL();
        exit(1);
    }; */
    normal.font = loadAsset("assets/fonts/ka1.ttf");
    highlight.font = normal.font;
    info.font = loadAsset("assets/fonts/Monaco.ttf");
    score.font = info.font;
    game_over.font = normal.font;
    gestore_eventi =  &menu;


    while (!quit) {
        handleInput();
        if(gestore_eventi == &game){
            //TODO Silly issue we should reset the timer related to movement when we move
            drawGame();
        }
        if(gestore_eventi == &gameover){
            drawGameover(playerOne);
        }
        if(gestore_eventi == &menu){
            drawMenu();
        }
        if(gestore_eventi == &pause) {
            drawPause();
        }
        if(gestore_eventi == &credits){
            drawCredits();
        }
    }

}
