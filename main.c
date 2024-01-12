#include <stdio.h>

#define BOARD_SIZE 3

// typedef struct Board {

// } Board;

int check_Board_Score(int board[BOARD_SIZE][BOARD_SIZE]);

int main() {
    //0 = empty
    //1 = x, -1 = o
    int board[BOARD_SIZE][BOARD_SIZE] = {
            { 1, 1,  1},
            {-1, -1,  1}, 
            { 0,  0,  0}
        };
    check_Board_Score(board);
    return 0;
}

int check_Board_Score(int board[BOARD_SIZE][BOARD_SIZE]) {
    //Check rows for win
    for (int i = 0; i < BOARD_SIZE; i++) {
        int sum = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            sum += board[i][j];
        }
        if (sum == BOARD_SIZE) {
            printf("Found a winning solution for x");
            return 10;
        }
        if (sum == -BOARD_SIZE) {
            printf("Found a winning solution for o");
            return -10;
        }
        printf("Sum for row %d is : %d \n", i, sum);
    }
    return 0;
}