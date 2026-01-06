#include "drawing.h"


void clearScreen(){
    system("cls");
}

void drawGame(Game* game) {
    if (game == NULL) return;
    
    clearScreen();
    
    printf("TETRIS | Score: %d | Frame: %d\n", game->score, game->frameCount);
    printf("+");
    for (int i = 0; i < WIDTH * 2; i++) printf("-");
    printf("+\n");
    
    char display[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            display[i][j] = board[i][j] ? '#' : ' ';
        }
    }
    
    if (game->currentFig != NULL) {
        Tetr* fig = game->currentFig;
        for (int py = 0; py < 4; py++) {
            for (int px = 0; px < 4; px++) {
                if (fig->shape[py][px]) {
                    int bx = fig->x + px;
                    int by = fig->y + py;
                    if (by >= 0 && by < HEIGHT && bx >= 0 && bx < WIDTH) {
                        display[by][bx] = '@';
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < HEIGHT; i++) {
        printf("|");
        for (int j = 0; j < WIDTH; j++) {
            printf("%c ", display[i][j]);
        }
        printf("|");
        
        if (i == 1) printf("  Control:");
        else if (i == 3) printf("  A - left");
        else if (i == 4) printf("  D - right");
        else if (i == 5) printf("  S - down");
        
        printf("\n");
    }
    
    printf("+");
    for (int i = 0; i < WIDTH * 2; i++) printf("-");
    printf("+\n");

    printf("Next: \n\n  ");
    if (game->nextFig != NULL) {
        Tetr* fig = game->nextFig;
        for (int py = 0; py < 4; py++) {
            for (int px = 0; px < 4; px++) {
                if (fig->shape[py][px] == 1) printf("#");
                else printf(" ");
            }
            printf("\n  ");
        }
    }
    
    if (game->isLose) {
        printf("\n=====================\n");
        printf("      GAME OVER!     \n");
        printf("=====================\n");
    }
}
