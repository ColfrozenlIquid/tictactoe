#include <stdio.h>
#include <stdlib.h>
#define BOARD_SIZE 3

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct Move {
    int row;
    int col;
} Move;

int check_Board_Score(int board[BOARD_SIZE][BOARD_SIZE]);
int check_Moves_Left(int board[BOARD_SIZE][BOARD_SIZE]);
Move calculate_Best_Move(int board[BOARD_SIZE][BOARD_SIZE]);
int minimax(int board[BOARD_SIZE][BOARD_SIZE], int depth, int turn);

int main() {
    //0 = empty
    //1 = x, -1 = o
    int board[BOARD_SIZE][BOARD_SIZE] = {
            { 1, -1,  1},
            {-1, -1,  1}, 
            { 0,  0,  0}
        };
    //check_Board_Score(board);
    Move bestmove = calculate_Best_Move(board);
    printf("Best move is row: %d, col: %d", bestmove.row, bestmove.col);
    return 0;
}

int minimax(int board[BOARD_SIZE][BOARD_SIZE], int depth, int turn) {
    int current_board_score = check_Board_Score(board);
    //Check for win condition
    if (current_board_score == 10 || current_board_score == -10) {
        return current_board_score;
    }
    //check for tie condition
    if (check_Moves_Left(board) == 0) {
        return 0;
    }
    switch (turn) {
    case 1:
        {
            int best = -INT_MAX;
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (board[i][j] == 0) {
                        board[i][j] = 1;
                        best = MAX(best, minimax(board, depth+1, !turn));
                        board[i][j] = 0;
                    }
                }
            }
            return best;
        }
        break;
    case 0:
        {
            int best = INT_MAX;
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (board[i][j] == 0) {
                        board[i][j] = -1;
                        best = MAX(best, minimax(board, depth+1, !turn));
                        board[i][j] = 0;
                    }
                }
            }
            return best;
        }
    default:
        break;
    }
}

Move calculate_Best_Move(int board[BOARD_SIZE][BOARD_SIZE]) {
    int best_move_val = -INT_MAX;
    Move move = {move.col = 0, move.row = 0};
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                
                board[i][j] = 1;
                int move_Value = minimax(board, 0, 0);
                board[i][j] = 0;

                if (move_Value > best_move_val) {
                    move.row = i;
                    move.col = j;
                }
            }
        }
    }
    return move;
}

int check_Moves_Left(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                return 1;
            }
        }
    }
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
            //printf("Found a winning solution for x on row: %d\n", i);
            return 10;
        }
        if (sum == -BOARD_SIZE) {
            //printf("Found a winning solution for o on row: %d", i);
            return -10;
        }
        //printf("Sum for row %d is : %d \n", i, sum);
    }
    //check columns for win
    for (int i = 0; i < BOARD_SIZE; i++) {
        int sum = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            sum += board[j][i];
        }
        if (sum == BOARD_SIZE) {
            //printf("Found a winning solution for x on column: %d\n", i);
            return 10;
        }
        if (sum == -BOARD_SIZE) {
            //printf("Found a winning solution for o on column: %d\n", i);
            return -10;
        }
        //printf("Sum for column %d is : %d \n", i, sum);
    }
    //check diagonals for win
    {
        int sum1 = 0;
        int sum2 = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            sum1 += board[i][i];
            sum2 += board[i][BOARD_SIZE-i-1];
        }
        if (sum1 == BOARD_SIZE) {
            //printf("Found a winning solution for x on \\ diagonal\n");
            return 10;
        }
        if (sum1 == -BOARD_SIZE) {
            //printf("Found a winning solution for x on \\ diagonal\n");
            return -10;
        }
        if (sum2 == BOARD_SIZE) {
            //printf("Found a winning solution for x on / diagonal\n");
            return 10;
        }
        if (sum2 == -BOARD_SIZE) {
            //printf("Found a winning solution for x on / diagonal\n");
            return -10;
        }
        //printf("Sum for \\ diagonal is : %d \n", sum1);
        //printf("Sum for / diagonal is : %d \n", sum2);
    }
    return 0;
}