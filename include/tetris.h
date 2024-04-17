#ifndef PEZZITETRIS_SHAPE_H
#define PEZZITETRIS_SHAPE_H
#include "../include/easy_sdl.h"
const int MAX = 4;

const int SHAPE_WIDTH = MAX;
const int SHAPE_HEIGHT = MAX;
const int FALL_SPEED_LIMIT = 100;

const int WORLD_HEIGHT = 24 + 4;
const int WORLD_WIDTH = 10;
const char EMPTY_SPACE = ' ';

const int N_BLOCKS= 7;
const int ROTATION = 4;

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
    int fallSpeed = 1000;
    int lastTime = 0;

} World_Data_t;


//Forma I
extern char blocks[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH];

//void stampa(char Mat[][SHAPE_HEIGHT][SHAPE_WIDTH], const int MAX);

bool gameOver(Player_Data_t playerOne, World_Data_t currentGame, char shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH],
              char world[WORLD_HEIGHT][WORLD_WIDTH]);

bool isColliding(int y, int x, int rotation, Player_Data_t playerOne, World_Data_t currentGame, char  shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH],
              char world[WORLD_HEIGHT][WORLD_WIDTH]);

void placeIt(Player_Data_t playerOne, World_Data_t currentGame, char  shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH],
              char world[WORLD_HEIGHT][WORLD_WIDTH], int& currentScore);

bool isLineComplete(int line, char world[WORLD_HEIGHT][WORLD_WIDTH]);

void deleteLine(int line, char world[WORLD_HEIGHT][WORLD_WIDTH]);

void fallDown(Player_Data_t playerOne, World_Data_t currentGame, char  shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH],
              char world[WORLD_HEIGHT][WORLD_WIDTH], int& currentScore);

void initWorld(char world[WORLD_HEIGHT][WORLD_WIDTH]);

int randIndex();

void updateScore(Player_Data_t playerOne, int lineCleared, int& currentScore);

void upgradeLevel(int targetScore, int& currentLevel, int& fallSpeed, int& MaxFallSpeed);

void setupNewGames(Player_Data_t& player, World_Data_t& world, char map[WORLD_HEIGHT][WORLD_WIDTH]);

#endif //PEZZITETRIS_SHAPE_H

