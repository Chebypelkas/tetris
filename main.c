#include "generic.h"
#include "figure.h"
#include "drawing.h"


int main() {
    Game *game = initGame();
    if (game == NULL) {
        printf("Game initialization error!\n");
        return 1;
    }

    printf("Tetris (simple version)\n");
    printf("Figures fall and fix at the bottom\n");
    printf("Control: A-left, D-right, S-down, X-rotate left, C-rotate right, ESC-exit\n");
    printf("Press any key to start...\n");
    getch();

    while (!game->isLose) {
        if (kbhit()) {
            int key = getch();
            
            if (key == 0 || key == 224) {
                key = getch();
                
                switch (key) {
                    case 75:  // Стрелка влево
                        moveFigure(game, -1, 0);
                        break;
                    case 77:  // Стрелка вправо
                        moveFigure(game, 1, 0);
                        break;
                    case 80:  // Стрелка вниз
                        moveFigure(game, 0, 1);
                        break;
                }
            } 
            else {
                switch (key) {
                    case 'a': case 'A':  // Влево
                        moveFigure(game, -1, 0);
                        break;
                    case 'd': case 'D':  // Вправо
                        moveFigure(game, 1, 0);
                        break;
                    case 's': case 'S':  // Вниз
                        moveFigure(game, 0, 1);
                        break;
                    case 'q': case 'Q':  // Поворот против часовой
                    case 'z': case 'Z':
                        rotateFigure(game->currentFig, -1);
                        break;
                    case 'e': case 'E':  // Поворот по часовой
                    case 'x': case 'X':
                        rotateFigure(game->currentFig, 1);
                        break;
                    case ' ':  // Пробел - мгновенное падение
                        while (!checkCollision(game->currentFig, 0, 1)) {
                            game->currentFig->y++;
                        }
                        moveFigure(game, 0, 1);
                        break;
                    case 27:  // ESC
                        game->isLose = true;
                        break;
                }
            }
        }
        
        game->frameCount++;
        if (game->frameCount % FALL_SPEED == 0) {
            moveFigure(game, 0, 1);
        }

        drawGame(game);
        
        Sleep(FRAME_DELAY);
    }

    drawGame(game);
    printf("\nGame over! Final score: %d\n", game->score);
    printf("Press any key to exit...\n");
    getch();

    deleteTetr(game->currentFig);
    deleteTetr(game->nextFig);
    free(game);

    return 0;
}
