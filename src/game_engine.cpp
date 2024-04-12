#include <iostream>
//#include "../include/shape.h"
//#include "../include/game_engine.h"
#include "../include/tetris.h"


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
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
            },
             {
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
            },
             {
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
                {'*',' ',' ',' '},
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


void stampa(char Mat[][SHAPE_HEIGHT][SHAPE_WIDTH], const int MAX){
    for(int k = 0; k < MAX; k++){
        for(int i = 0; i < SHAPE_HEIGHT; i++){
            for (int j = 0; j < SHAPE_WIDTH; j++){
                std::cout << Mat[k][i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "---------------\n";
    }
}


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
                else if(world[worldY][worldX] == '1' && shape[N_BLOCKS][typeShape][i][j] == '*'){
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
            if (shape[N_BLOCKS][typeShape][i][j] == '*') {
                int worldX = x + j;
                int worldY = y + i;
                world[worldY][worldX] = '*';
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
        if(world[line][i] != '1'){
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
        world[0][j] = '0';
    }
}

void fallDown(int x, int y, char shape[N_BLOCKS][ROTATION][SHAPE_HEIGHT][SHAPE_WIDTH], int typeShape,
              char world[WORLD_HEIGHT][WORLD_WIDTH]) {

    while (!isColliding(y + 1, x, shape, typeShape, world)) {
        y++;
    }

    placeIt(y, x, shape, typeShape, world);
}
