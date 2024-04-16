#include <iostream>
#include "../include/tetris.h"
#include <random>
#include <ctime>

using namespace std;

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
                        {'6','6',' ',' ' },
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


bool isColliding(int y, int x, int rotation, char shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH], int typeShape,
                  char world[WORLD_HEIGHT][WORLD_WIDTH], Player_Data_t playerOne){
    bool collision = false;

    int shapeRows = SHAPE_HEIGHT;
    int shapeCols = SHAPE_WIDTH;

    for(int i = 0; i < shapeRows;i++){
        for(int j = 0; j < shapeCols; j++){
            if (shape[playerOne.assetIdx][rotation][i][j] != EMPTY_SPACE ) {
                int worldY = y + i;
                int worldX = x + j;

                if (worldX < 0 || worldX >= WORLD_WIDTH || worldY < 0 || worldY >= WORLD_HEIGHT) {
                    collision = true;
                }

                    collision = true;
                if(world[worldY][worldX] != EMPTY_SPACE ){
                }
            }
        }
    }

    return collision;
}


void placeIt(int y, int x, int rotation, char shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH], int typeShape,
                  char world[WORLD_HEIGHT][WORLD_WIDTH], Player_Data_t playerOne, int& currentScore){

    for(int i = 0; i < SHAPE_HEIGHT; i++){
        for(int j = 0; j < SHAPE_WIDTH; j++){
            if (shape[playerOne.assetIdx][rotation][i][j] != EMPTY_SPACE ) {
                int worldX = x + j;
                int worldY = y + i;
                world[worldY][worldX] = shape[playerOne.assetIdx][rotation][i][j];
            }
        }
    }

    int deletedLines = 0;

    if(deletedLines == 0) {
        currentScore += 30;
    }
    else{
        for(int i = 0; i < WORLD_HEIGHT; i++) {
        if(isLineComplete(i, world)) {
            deleteLine(i, world);
            deletedLines++;
        }
    }
    updateScore(currentScore, deletedLines);

    }

}

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
        world[0][j] = EMPTY_SPACE;
    }
}

void fallDown(int x, int y, int rotation, char  shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH], int typeShape,
              char world[WORLD_HEIGHT][WORLD_WIDTH], Player_Data_t playerOne, int& currentScore) {

    while (!isColliding(y + 1, x,rotation, shape, typeShape, world, playerOne)) {
        y++;
    }
    placeIt(y, x, rotation, shape, typeShape, world, playerOne, currentScore);
}

void initWorld(char world[WORLD_HEIGHT][WORLD_WIDTH]){
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

    int targetScore = currentLevel * 500 + 500;

    if(currentScore >= targetScore) {
        fallSpeed -= 200;
        currentLevel++;
    }
    if(fallSpeed > MaxFallSpeed) {
        fallSpeed = MaxFallSpeed;
    }
}

//TODO risolvere il problema del crash
int randIndex() {

    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 6);

    int val = dis(gen);
    cout << val << endl;
    return val;
}



void setupNewGames(Player_Data_t& player, World_Data_t& world, char map[WORLD_HEIGHT][WORLD_WIDTH]) {
    player.score = 0;
    player.rotation=0;
    world.level = 1;
    world.fallSpeed= 1000;
    initWorld(map);
    player.assetIdx = randIndex();
   // player.assetIdx = 6;
    world.nextBlock = randIndex();
    player.x = 3;
    player.y =  0;
}

