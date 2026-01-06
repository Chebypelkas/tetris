#include "figure.h"


static const int ALL_SHAPES[7][4][4] = {
    {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}},
    {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    {{0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
    {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}}
};


void copyShape(int dest[4][4], const int src[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dest[i][j] = src[i][j];
        }
    }
}


Tetr *createTetr(int type) {
    if (type < 0 || type > 6) {
        return NULL;
    }

    Tetr* fig = (Tetr*)malloc(sizeof(Tetr));
    if (fig == NULL) {
        return NULL;
    }

    fig->type = type;
    fig->x = START_X;
    fig->y = START_Y;

    copyShape(fig->shape, ALL_SHAPES[type]);

    return fig;
}


void setPosTetr(Tetr* fig, int x, int y){
    if (fig == NULL) return;
    fig->x = x;
    fig->y = y;
}

void deleteTetr(Tetr* fig) {
    if (fig != NULL) free(fig);
}

Tetr* createRandomTetr(){
    return createTetr(rand() % 7);
}

