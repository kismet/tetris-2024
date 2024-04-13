#include <iostream>
#include "../include/tetris.h"

//TODO verificare che il VUOTO sia ' ' nel MONDO e non ZERO e non UNO
//TODO aggiornare le funzioni deleteLine per punti ed eventualmente velocità



char blocks[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH] = {
        //I
        {
                {
                        {'1',' ',' ',' '},
                        {'1',' ',' ',' '},
                        {'1',' ',' ',' '},
                        {'1',' ',' ',' '},
                },
                {
                        {'1','1','1','1'},
                        {' ',' ',' ',' '},
                        {' ',' ',' ',' '},
                        {' ',' ',' ',' '},
                },
                {
                        {'1',' ',' ',' '},
                        {'1',' ',' ',' '},
                        {'1',' ',' ',' '},
                        {'1',' ',' ',' '},
                },
                {
                        {'1','1','1','1'},
                        {' ',' ',' ',' '},
                        {' ',' ',' ',' '},
                        {' ',' ',' ',' '},
                },
        },

        //J
        {
                {
                        {'2',' ',' ',' ' },
                        {'2','2','2',' ' },
                        {' ',' ',' ',' ' },
                        {' ',' ',' ',' ' },
                },

                {
                        {'2','2',' ',' ' },
                        {'2',' ',' ',' ' },
                        {'2',' ',' ',' ' },
                        {' ',' ',' ',' ' },
                },

                {
                        {'2','2','2',' ' },
                        {' ',' ','2',' ' },
                        {' ',' ',' ',' ' },
                        {' ',' ',' ',' ' },
                },
                {
                        {' ','2',' ',' ' },
                        {' ','2',' ',' ' },
                        {'2','2',' ',' ' },
                        {' ',' ',' ',' ' },
                }
        },

        //L
        {
                {
                        {'3','3',' ',' '},
                        {' ','3',' ',' ' },
                        {' ','3',' ',' ' },
                        {' ',' ',' ',' '},
                },
                {
                        {' ',' ','3',' '},
                        {'3','3','3',' ' },
                        {' ',' ',' ',' ' },
                        {' ',' ',' ',' '},
                },
                {
                        {'3',' ',' ',' '},
                        {'3',' ',' ',' ' },
                        {'3','3',' ',' ' },
                        {' ',' ',' ',' '},
                },
                {
                        {'3','3','3',' '},
                        {'3',' ',' ',' ' },
                        {' ',' ',' ',' ' },
                        {' ',' ',' ',' '},
                }
        },

        //O
        {
                {
                        {'4','4',' ',' ' },
                        {'4','4',' ',' ' },
                        {' ',' ',' ',' ' },
                        {' ',' ',' ',' ' },
                },
                {
                        {'4','4',' ',' ' },
                        {'4','4',' ',' ' },
                        {' ',' ',' ',' ' },
                        {' ',' ',' ',' ' },
                },
                {
                        {'4','4',' ',' ' },
                        {'4','4',' ',' ' },
                        {' ',' ',' ',' ' },
                        {' ',' ',' ',' ' },
                },
                {
                        {'4','4',' ',' ' },
                        {'4','4',' ',' ' },
                        {' ',' ',' ',' ' },
                        {' ',' ',' ',' ' },
                },
        },

        //S
        {
                {
                        {' ','5','5',' '},
                        {'5','5',' ',' '},
                        {' ',' ',' ',' '},
                        {' ',' ',' ',' '},
                },
                {
                        {'5',' ',' ',' '},
                        {'5','5',' ',' '},
                        {' ','5',' ',' '},
                        {' ',' ',' ',' '},
                },
                {
                        {' ','5','5',' '},
                        {'5','5',' ',' '},
                        {' ',' ',' ',' '},
                        {' ',' ',' ',' '},
                },
                {
                        {'5',' ',' ',' '},
                        {'5','5',' ',' '},
                        {' ','5',' ',' '},
                        {' ',' ',' ',' '},
                },
        },

        //T
        {
                {
                        {' ','6',' ',' '},
                        {'6','6','6',' ' },
                        {' ',' ',' ',' '},
                        {' ',' ',' ',' '},
                },
                {
                        {'6',' ',' ',' '},
                        {'6','6',' ',' ' },
                        {'6',' ',' ',' '},
                        {' ',' ',' ',' '},
                },
                {
                        {'6','6','6',' '},
                        {' ','6',' ',' ' },
                        {' ',' ',' ',' '},
                        {' ',' ',' ',' '},
                },
                {
                        {' ','6',' ',' '},
                        {' ','6','6',' ' },
                        {' ','6',' ',' '},
                        {' ',' ',' ',' '},
                }
        },

        //|
        {
                {
                        {'7','7',' ',' ' },
                        {' ','7','7',' ' },
                        {' ',' ',' ',' '},
                        {' ',' ',' ',' ' },
                },
                {
                        {' ','7',' ',' ' },
                        {'7','7',' ',' ' },
                        {'7',' ',' ',' '},
                        {' ',' ',' ',' ' },
                },
                {
                        {'7','7',' ',' ' },
                        {' ','7','7',' ' },
                        {' ',' ',' ',' '},
                        {' ',' ',' ',' ' },
                },
                {
                        {' ','7',' ',' ' },
                        {'7','7',' ',' ' },
                        {'7',' ',' ',' '},
                        {' ',' ',' ',' ' },
                }
        }
};


bool isColliding(int y, int x, char shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH], int typeShape,
                  char world[WORLD_HEIGHT][WORLD_WIDTH]){
    bool collision = false;

    int shapeRows = SHAPE_HEIGHT;
    int shapeCols = SHAPE_WIDTH;

    for(int i = 0; i < shapeRows;i++){
        for(int j = 0; j < shapeCols; j++){
            if (shape[N_BLOCKS][typeShape][i][j] != ' ') {
                int worldY = y + i;
                int worldX = x + j;

                if (worldX < 0 || worldX >= WORLD_WIDTH || worldY < 0 || worldY >= WORLD_HEIGHT) {
                    collision = true;
                }
                if(world[worldY][worldX] != ' '){
                    collision = true;
                }
            }
        }
    }

    return collision;
}


void placeIt(int y,int x, char shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH], int typeShape,
             char world[WORLD_HEIGHT][WORLD_WIDTH]){
    for(int i = 0; i < SHAPE_HEIGHT; i++){
        for(int j = 0; j < SHAPE_WIDTH; j++){
            if (shape[N_BLOCKS][typeShape][i][j] != ' ') {
                int worldX = x + j;
                int worldY = y + i;
                world[worldY][worldX] = shape[N_BLOCKS][typeShape][i][j];
            }
        }
    }
}

/*
void placeCollide(int y,int x, char shape[][SHAPE_HEIGHT][SHAPE_WIDTH], int typeShape,
                   char world[WORLD_HEIGHT][WORLD_WIDTH]){
    for(int i = 0; i < SHAPE_HEIGHT; i++){
        for(int j = 0; j < SHAPE_WIDTH; j++){
            if (shape[typeShape][i][j] == '*') {
                int worldX = x + j;
                int worldY = y + i;
                world[worldY][worldX] = '1';
            }
        }
    }
}
*/
bool isLineComplete(int line, char world[WORLD_HEIGHT][WORLD_WIDTH]){
    bool isComplete = true;
    int i = 0;
    while(i < WORLD_WIDTH && isComplete){
        if(world[line][i] != ' '){
            isComplete = false;
        }
        i++;
    }
    return isComplete;
}

void deleteLine(int line, char world[WORLD_HEIGHT][WORLD_WIDTH]){
    for(int i = line; i > 0; i--) {
        for(int j = 0; j < WORLD_WIDTH; j++) {
            world[i][j] = world[i-1][j];
        }
    }
    for(int j = 0; j < WORLD_WIDTH; j++) {
        world[0][j] = ' ';
    }
}

void fallDown(int x, int y, char shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH], int typeShape,
              char world[WORLD_HEIGHT][WORLD_WIDTH]) {

    while (!isColliding(y + 1, x, shape, typeShape, world)) {
        y++;
    }

    placeIt(y, x, shape, typeShape, world);
}

void initworld(char** world){
    for(int i = 0; i < WORLD_HEIGHT; i++) {
        for (int j = 0; j < WORLD_WIDTH; j++) {
            world[i][j] = EMPTY_SPACE;
        }
    }
}

//TODO funzione updateScore invocata da deleteLine e da placeIt che aggiorna il punteggio
void updateScore(int& currentScore, int lineCleared) {
    int points[] = {100, 200, 400, 800};

    currentScore += points[lineCleared];
}

//TODO funzione per upgradeLevel controlla il numero di linee o punteggio e aumenta velocità
void upgradeLevel(int currentScore,int&currentLevel, int& fallSpeed, int& MaxFallSpeed) {

    int targetScore = currentLevel * 10000 + 10000;

    if(currentScore >= targetScore) {
        fallSpeed += 100; //TODO verificare se la velocita e' adeguata
        currentLevel++;
    }
    if(fallSpeed > MaxFallSpeed) {
        fallSpeed = MaxFallSpeed;
    }
}


