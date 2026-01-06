#include "generic.h"
#include "figure.h"


int board[HEIGHT][WIDTH] = {0};


Game *initGame(){
    Game *game = (Game*)malloc(sizeof(Game));
    if (game == NULL) return NULL;

    srand(time(NULL));

    Tetr *curTetr = createRandomTetr();
    if (curTetr == NULL) return NULL;
    Tetr *nextTetr = createRandomTetr();
    if (nextTetr == NULL) {
        deleteTetr(curTetr);
        return NULL;
    }

    game->isLose = false;
    game->currentFig = curTetr;
    game->nextFig = nextTetr;
    game->frameCount = 0;
    game->score = 0;

    return game;
}


int checkCollision(Tetr* fig, int dx, int dy){
    if (fig == NULL) return 1;

    for (int py = 0; py < 4; py++){
        for (int px = 0; px < 4; px++){
            if (fig->shape[py][px] == 1){
                int newX = fig->x + px + dx;
                int newY = fig->y + py + dy;
                
                // Пересечение с границей поля
                if (newX < 0 || newX >= WIDTH || newY >= HEIGHT) {
                    return 1;
                }
                
                // Пересечение с другими фигурами
                if (newY >= 0 && board[newY][newX]) {
                    return 1;
                }
            }
        }
    }

    return 0;
}


void moveFigure(Game* game, int dx, int dy){
    if (game == NULL || game->currentFig == NULL) return;

    if (checkCollision(game->currentFig, dx, dy) == 0){
        game->currentFig->x += dx;
        game->currentFig->y += dy;
    }
    else if (dy > 0){
        mergeFigureToBoard(game);

        deleteTetr(game->currentFig);
        game->currentFig = game->nextFig;
        game->nextFig = createRandomTetr();

        if (checkCollision(game->currentFig, 0, 0)) {
            game->isLose = true;
        }
    }
}


int rotateFigure(Tetr* fig, int dirRotate) {
    if (fig == NULL) return 0;
    
    if (fig->type == 3) return 1;

    int originalShape[4][4];
    int originalX = fig->x;
    int originalY = fig->y;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            originalShape[i][j] = fig->shape[i][j];
        }
    }
    
    if (dirRotate == 1) {  // По часовой стрелке
        int temp[4][4];
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                temp[i][j] = fig->shape[i][j];
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                fig->shape[j][3 - i] = temp[i][j];
    } 
    else if (dirRotate == -1) {  // Против часовой стрелки
        int temp[4][4];
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                temp[i][j] = fig->shape[i][j];
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                fig->shape[3 - j][i] = temp[i][j];
    }
    else {
        return 0;
    }
    
    int kicks[5][2] = {
        {0, 0},   // тест 0: без смещения
        {-1, 0},  // тест 1: влево
        {1, 0},   // тест 2: вправо
        {0, -1},  // тест 3: вверх
        {0, 1}    // тест 4: вниз
    };
    
    int iKicks[5][2] = {
        {0, 0},
        {-2, 0},
        {1, 0},
        {-2, -1},
        {1, 2}
    };
    
    int (*kickTable)[2] = (fig->type == 0) ? iKicks : kicks;
    
    for (int i = 0; i < 5; i++) {
        int dx = kickTable[i][0];
        int dy = kickTable[i][1];
        
        if (!checkCollision(fig, dx, dy)) {
            fig->x += dx;
            fig->y += dy;
            return 1;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            fig->shape[i][j] = originalShape[i][j];
        }
    }
    fig->x = originalX;
    fig->y = originalY;
    
    return 0;
}


void mergeFigureToBoard(Game* game) {
    if (game == NULL || game->currentFig == NULL) return;
    
    Tetr* fig = game->currentFig;
    
    for (int py = 0; py < 4; py++) {
        for (int px = 0; px < 4; px++) {
            if (fig->shape[py][px]) {
                int board_x = fig->x + px;
                int board_y = fig->y + py;
                
                if (board_y >= 0 && board_x >= 0 && board_x < WIDTH) {
                    board[board_y][board_x] = 1;
                    game->score += 10;
                }
            }
        }
    }

    clearLine(game);
}


void clearLine(Game* game){
    if (game == NULL) return;
    
    int linesCleared = 0;
    
    for (int y = HEIGHT - 1; y >= 0; y--) {
        int lineFull = 1;
        
        for (int x = 0; x < WIDTH; x++) {
            if (board[y][x] == 0) {
                lineFull = 0;
                break;
            }
        }
        
        if (lineFull) {
            linesCleared++;
            
            for (int ny = y; ny > 0; ny--) {
                for (int x = 0; x < WIDTH; x++) {
                    board[ny][x] = board[ny - 1][x];
                }
            }
            
            for (int x = 0; x < WIDTH; x++) {
                board[0][x] = 0;
            }
            
            y++;
        }
    }
    
    if (linesCleared > 0) {
        switch (linesCleared) {
            case 1:
                game->score += 100;
                break;
            case 2:
                game->score += 300;
                break;
            case 3:
                game->score += 500;
                break;
            case 4:
                game->score += 800;
                break;
        }
    }
}
