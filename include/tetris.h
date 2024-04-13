#ifndef PEZZITETRIS_SHAPE_H
#define PEZZITETRIS_SHAPE_H

const int MAX = 4;

const int SHAPE_WIDTH = MAX;
const int SHAPE_HEIGHT = MAX;

const int WORLD_HEIGHT = 24 + 4;
const int WORLD_WIDTH = 10;
const char EMPTY_SPACE = ' ';

const int N_BLOCKS= 7;
const int ROTATION = 4;

//Forma I
extern char blocks[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH];

//void stampa(char Mat[][SHAPE_HEIGHT][SHAPE_WIDTH], const int MAX);


bool isColliding(int y, int x, char shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH], int typeShape,
                  char world[WORLD_HEIGHT][WORLD_WIDTH]);

void placeIt(int y,int x, char shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH], int typeShape,
             char world[WORLD_HEIGHT][WORLD_WIDTH], int& currentScore);

bool isLineComplete(int line, char world[WORLD_HEIGHT][WORLD_WIDTH]);

void deleteLine(int line, char world[WORLD_HEIGHT][WORLD_WIDTH]);

void fallDown(int x, int y, char shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH], int typeShape,
              char world[WORLD_HEIGHT][WORLD_WIDTH], int& currentScore);

void initworld(char world[WORLD_HEIGHT][WORLD_WIDTH]);

void updateScore(int& currentScore, int lineCleared);

void upgradeLevel(int currentScore,int&currentLevel, int& fallSpeed, int& MaxFallSpeed);


#endif //PEZZITETRIS_SHAPE_H

