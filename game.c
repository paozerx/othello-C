#include <stdio.h>

#define SIZE 8
#define EMPTY '.'
#define MARK '*'
#define BLACK 'B'
#define WHITE 'W'

char board[SIZE][SIZE];
char current = WHITE;
char another = BLACK;
int coinWhite = 0;
int coinBlack = 0;

void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    board[3][3] = WHITE;
    board[3][4] = BLACK;
    board[4][3] = BLACK;
    board[4][4] = WHITE;
}

void displayBoard() {
    printf("  ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void checkScore() {
    coinWhite = 0;
    coinBlack = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == BLACK) coinBlack++;
            if (board[i][j] == WHITE) coinWhite++;
        }
    }
}

int canFlip(int row, int col, int dr, int dc) {
    int nr = row + dr;
    int nc = col + dc;
    int hasOpponentBetween = 0;

    while (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE) {
        if (board[nr][nc] == EMPTY || board[nr][nc] == MARK) return 0;
        if (board[nr][nc] == another) {
            hasOpponentBetween = 1;
        } else if (board[nr][nc] == current) {
            return hasOpponentBetween;
        }
        nr += dr;
        nc += dc;
    }
    return 0;
}

int canPlaceMarker(int row, int col) {
    int directions[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };
    for (int i = 0; i < 8; i++) {
        if (canFlip(row, col, directions[i][0], directions[i][1])) {
            return 1;
        }
    }
    return 0;
}

void markerValidMove() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY && canPlaceMarker(i, j)) {
                board[i][j] = MARK;
            }
        }
    }
}

void playFlips(int row, int col, int dr, int dc) {
    int nr = row + dr;
    int nc = col + dc;

    while (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE) {
        if (board[nr][nc] == another) {
            board[nr][nc] = current;
        } else if (board[nr][nc] == current) {
            break;
        }
        nr += dr;
        nc += dc;
    }
}

void sendInfoPlay(int row, int col) {
    int directions[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };
    for (int i = 0; i < 8; i++) {
        playFlips(row, col, directions[i][0], directions[i][1]);
    }
}

void removeMark() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == MARK) {
                board[i][j] = EMPTY;
            }
        }
    }
}

int isGameOver() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == MARK) return 0;
        }
    }
    return 1;
}

void swapTurn() {
    char temp = current;
    current = another;
    another = temp;
}

void playGame() {
    while (1) {
        markerValidMove();
        displayBoard();
        printf("\nW: %d     B: %d\n\n", coinWhite, coinBlack);

        if (isGameOver()) {
            if (coinWhite > coinBlack) {
                printf("Player W wins!\n");
            } else if (coinWhite < coinBlack) {
                printf("Player B wins!\n");
            } else {
                printf("It's a draw!\n");
            }
            break;
        }

        int row, col;
        printf("%c's turn. Enter row: ", current);
        scanf("%d", &row);
        printf("%c's turn. Enter column: ", current);
        scanf("%d", &col);
        printf("\n");

        if (row <= 0 || row > SIZE || col <= 0 || col > SIZE || board[row - 1][col - 1] != MARK) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        board[row - 1][col - 1] = current;
        sendInfoPlay(row - 1, col - 1);
        removeMark();
        checkScore();
        swapTurn();
    }
}

int main() {
    initializeBoard();
    playGame();
    return 0;
}
