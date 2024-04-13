#include <iostream>
#include "../include/tetris.h"

//TODO modificare '*' con indice dell'assets da usare per la visualizzazione
//TODO verificare che il VUOTO sia ' ' nel MONDO e non ZERO e non UNO
//TODO aggiornare le funzioni deleteLine per punti ed eventualmente velocità

//TODO funzione per upgradeLevel controlla il numero di linee o punteggio e aumenta velocità



char blocks[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH] = {
        //I
        {
            {
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
            },
            {
                {'*','*','*','*'},
                {' ',' ',' ',' '},
                {' ',' ',' ',' '},
                {' ',' ',' ',' '},
            },
             {
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
            },
             {
                {'*','*','*','*'},
                {' ',' ',' ',' '},
                {' ',' ',' ',' '},
                {' ',' ',' ',' '},
            },
        },

        //J
        {
            {
                {'*',' ',' ',' ' },
                {'*','*','*',' ' },
                {' ',' ',' ',' ' },
                {' ',' ',' ',' ' },
            },

            {
                {'*','*',' ',' ' },
                {'*',' ',' ',' ' },
                {'*',' ',' ',' ' },
                {' ',' ',' ',' ' },
            },

            {
                {'*','*','*',' ' },
                {' ',' ','*',' ' },
                {' ',' ',' ',' ' },
                {' ',' ',' ',' ' },
            },
            {
                {' ','*',' ',' ' },
                {' ','*',' ',' ' },
                {'*','*',' ',' ' },
                {' ',' ',' ',' ' },
            }
        },

        //L
        {
            {
                {'*','*',' ',' '},
                {' ','*',' ',' ' },
                {' ','*',' ',' ' },
                {' ',' ',' ',' '},
            },
            {
                {' ',' ','*',' '},
                {'*','*','*',' ' },
                {' ',' ',' ',' ' },
                {' ',' ',' ',' '},
            },
            {
                {'*',' ',' ',' '},
                {'*',' ',' ',' ' },
                {'*','*',' ',' ' },
                {' ',' ',' ',' '},
            },
            {
                {'*','*','*',' '},
                {'*',' ',' ',' ' },
                {' ',' ',' ',' ' },
                {' ',' ',' ',' '},
            }
        },

        //O
        {
             {
                {'*','*',' ',' ' },
                {'*','*',' ',' ' },
                {' ',' ',' ',' ' },
                {' ',' ',' ',' ' },
            },
            {
                {'*','*',' ',' ' },
                {'*','*',' ',' ' },
                {' ',' ',' ',' ' },
                {' ',' ',' ',' ' },
            },
            {
                {'*','*',' ',' ' },
                {'*','*',' ',' ' },
                {' ',' ',' ',' ' },
                {' ',' ',' ',' ' },
            },
            {
                {'*','*',' ',' ' },
                {'*','*',' ',' ' },
                {' ',' ',' ',' ' },
                {' ',' ',' ',' ' },
            },
        },

       //S
        {
            {
                {' ','*','*',' '},
                {'*','*',' ',' '},
                {' ',' ',' ',' '},
                {' ',' ',' ',' '},
            },
            {
                {'*',' ',' ',' '},
                {'*','*',' ',' '},
                {' ','*',' ',' '},
                {' ',' ',' ',' '},
            },
            {
                {' ','*','*',' '},
                {'*','*',' ',' '},
                {' ',' ',' ',' '},
                {' ',' ',' ',' '},
            },
            {
                {'*',' ',' ',' '},
                {'*','*',' ',' '},
                {' ','*',' ',' '},
                {' ',' ',' ',' '},
            },
        },

        //T
        {
            {
                {' ','*',' ',' '},
                {'*','*','*',' ' },
                {' ',' ',' ',' '},
                {' ',' ',' ',' '},
            },
            {
                {'*',' ',' ',' '},
                {'*','*',' ',' ' },
                {'*',' ',' ',' '},
                {' ',' ',' ',' '},
            },
            {
                {'*','*','*',' '},
                {' ','*',' ',' ' },
                {' ',' ',' ',' '},
                {' ',' ',' ',' '},
            },
            {
                {' ',' ','*',' '},
                {' ','*','*',' ' },
                {' ',' ','*',' '},
                {' ',' ',' ',' '},
            }
        },

        //|
        {
            {
                {'*','*',' ',' ' },
                {' ','*','*',' ' },
                {' ',' ',' ',' '},
                {' ',' ',' ',' ' },
            },
            {
                {' ','*',' ',' ' },
                {'*','*',' ',' ' },
                {'*',' ',' ',' '},
                {' ',' ',' ',' ' },
            },
            {
                {'*','*',' ',' ' },
                {' ','*','*',' ' },
                {' ',' ',' ',' '},
                {' ',' ',' ',' ' },
            },
            {
                {' ','*',' ',' ' },
                {'*','*',' ',' ' },
                {'*',' ',' ',' '},
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
                if (world[worldY][worldX] == ' ' && shape[N_BLOCKS][typeShape][i][j] == '*') {
                    collision = false;
                }
                else if(world[worldY][worldX] == ' ' && shape[N_BLOCKS][typeShape][i][j] == '*'){
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

    currentScore += points[lineCleaned];
}

