#ifndef GENERIC_H
#define GENERIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


#define FRAME_DELAY 50
#define FALL_SPEED 10

#define WIDTH 10
#define HEIGHT 20


extern int board[HEIGHT][WIDTH];

typedef struct Tetr{
    int type;
    int x, y;
    int shape[4][4];
} Tetr;

typedef struct Game{
    bool isLose;
    Tetr *currentFig;
    Tetr *nextFig;
    int frameCount;
    int score;
} Game;


Game *initGame();

void clearLine(Game* game);

#endif