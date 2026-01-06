#ifndef FIGURE_H
#define FIGURE_H

#include "generic.h"

#define START_X WIDTH / 2
#define START_Y 0


Tetr *createTetr(int type);

void setPosTetr(Tetr* fig, int x, int y);

void deleteTetr(Tetr* fig);

Tetr* createRandomTetr();


int checkCollision(Tetr* fig, int dx, int dy);

void moveFigure(Game* game, int dx, int dy);

int rotateFigure(Tetr* fig, int dirRotate);

void mergeFigureToBoard(Game* game);


#endif