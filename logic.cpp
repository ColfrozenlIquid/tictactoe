#include "logic.hpp"

void show_Best_Move(int board[BOARD_SIZE_LOGIC][BOARD_SIZE_LOGIC], Move best_move) {
    board[best_move.row][best_move.col] = 2;
    print_Board(board);
}


//Define: Board::
//  +---+---+---+
//  | x | Q |   |
//  +---+---+---+

#define X_ROW       " X |"
#define O_ROW       " O |"
#define B_ROW       " B |"
#define NULL_ROW    "   |"
#define BOTTOM_ROW  "---+"
#define WIDTH_ROW 5

void print_Board(int board[BOARD_SIZE_LOGIC][BOARD_SIZE_LOGIC]) {
    char top_line[BOARD_SIZE_LOGIC*WIDTH_ROW + 1];
    memset(top_line, 0, sizeof(top_line));
    strcat(top_line, "+");
    for (int h = 0; h < BOARD_SIZE_LOGIC; h++) {
        strcat(top_line, BOTTOM_ROW);
    }
    printf("%s\n", top_line);
    for (int i = 0; i < BOARD_SIZE_LOGIC; i++) {
        char line1[BOARD_SIZE_LOGIC*WIDTH_ROW + 1];
        char line2[BOARD_SIZE_LOGIC*WIDTH_ROW + 1];
        memset(line1, 0, sizeof(line1));
        memset(line2, 0, sizeof(line1));
        strcat(line1, "|");
        strcat(line2, "+");
        for (int j = 0; j < BOARD_SIZE_LOGIC; j++) {
            if (board[i][j] == -1) {
                strcat(line1, O_ROW);
            }
            if (board[i][j] == 2) {
                strcat(line1, B_ROW);
            }
            if (board[i][j] == 1) {
                strcat(line1, X_ROW);
            }
            if (board[i][j] == 0) {
                strcat(line1, NULL_ROW);
            }
            strcat(line2, BOTTOM_ROW);
        }
        printf("%s\n", line1);
        printf("%s\n", line2);
    }
}

Score minimax(int board[BOARD_SIZE_LOGIC][BOARD_SIZE_LOGIC], int depth, int turn) {
    int current_board_score = check_Board_Score(board);
    //Check for win condition
    if (current_board_score == 10 || current_board_score == -10) {
        Score score = {depth, current_board_score, 0};
        return score;
    }
    //check for tie condition
    if (check_Moves_Left(board) == 0) {
        Score score = {depth, current_board_score, 1};
        return score;
    }
    switch (turn) {
    case 0:
        {
            int best = -INT_MAX;
            for (int i = 0; i < BOARD_SIZE_LOGIC; i++) {
                for (int j = 0; j < BOARD_SIZE_LOGIC; j++) {
                    if (board[i][j] == 0) {
                        board[i][j] = 1;
                        best = MAX(best, minimax(board, depth+1, !turn).score);
                        board[i][j] = 0;
                    }
                }
            }
            Score score = {best, depth, 0};
            return score;
        }
        break;
    case 1:
        {
            int best = INT_MAX;
            for (int i = 0; i < BOARD_SIZE_LOGIC; i++) {
                for (int j = 0; j < BOARD_SIZE_LOGIC; j++) {
                    if (board[i][j] == 0) {
                        board[i][j] = -1;
                        best = MIN(best, minimax(board, depth+1, !turn).score);
                        board[i][j] = 0;
                    }
                }
            }
            Score score = {best, depth, 0};
            return score;
        }
    default:
        break;
    }
}

Move calculate_Best_Move(int board[BOARD_SIZE_LOGIC][BOARD_SIZE_LOGIC]) {
    int best_move_val = -INT_MAX;
    int best_depth = INT_MAX;
    Move move = {move.col = 0, move.row = 0};
    for (int i = 0; i < BOARD_SIZE_LOGIC; i++) {
        for (int j = 0; j < BOARD_SIZE_LOGIC; j++) {
            if (board[i][j] == 0) {
                
                board[i][j] = 1;
                Score best_move = minimax(board, 0, 0);
                board[i][j] = 0;
                //printf("Best_move.score: %d, best_move_val: %d\n", best_move.score, best_move_val);
                if (best_move.score > best_move_val ) {
                    if (best_move.depth <= best_depth) {
                        best_move_val = best_move.score;
                        move.row = i;
                        move.col = j;
                        best_depth = best_move.depth;
                    }
                    
                }
                //printf("Current best move is row: %d, columns: %d\n", move.row, move.col);
            }
        }
    }
    return move;
}

int check_Moves_Left(int board[BOARD_SIZE_LOGIC][BOARD_SIZE_LOGIC]) {
    for (int i = 0; i < BOARD_SIZE_LOGIC; i++) {
        for (int j = 0; j < BOARD_SIZE_LOGIC; j++) {
            if (board[i][j] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int check_Board_Score(int board[BOARD_SIZE_LOGIC][BOARD_SIZE_LOGIC]) {
    //Check rows for win
    for (int i = 0; i < BOARD_SIZE_LOGIC; i++) {
        //printf("Checking row: %d\n", i);
        int sum = 0;
        for (int j = 0; j < BOARD_SIZE_LOGIC; j++) {
            //printf("Checking columns: %d\n", j);
            sum += board[i][j];
        }
        if (sum == BOARD_SIZE_LOGIC) {
            //printf("Found a winning solution for x on row: %d\n", i);
            return 10;
        }
        if (sum == -BOARD_SIZE_LOGIC) {
            //printf("Found a winning solution for o on row: %d", i);
            return -10;
        }
        //printf("Sum for row %d is : %d \n", i, sum);
    }
    //check columns for win
    for (int i = 0; i < BOARD_SIZE_LOGIC; i++) {
        //printf("Checking column: %d\n", i);
        int sum = 0;
        for (int j = 0; j < BOARD_SIZE_LOGIC; j++) {
            //printf("Checking row: %d\n", j);
            sum += board[j][i];
        }
        if (sum == BOARD_SIZE_LOGIC) {
            //printf("Found a winning solution for x on column: %d\n", i);
            return 10;
        }
        if (sum == -BOARD_SIZE_LOGIC) {
            //printf("Found a winning solution for o on column: %d\n", i);
            return -10;
        }
        //printf("Sum for column %d is : %d \n", i, sum);
    }
    //check diagonals for win
    {
        int sum1 = 0;
        int sum2 = 0;
        for (int i = 0; i < BOARD_SIZE_LOGIC; i++) {
            sum1 += board[i][i];
            sum2 += board[i][BOARD_SIZE_LOGIC-i-1];
        }
        if (sum1 == BOARD_SIZE_LOGIC) {
            //printf("Found a winning solution for x on \\ diagonal\n");
            return 10;
        }
        if (sum1 == -BOARD_SIZE_LOGIC) {
            //printf("Found a winning solution for x on \\ diagonal\n");
            return -10;
        }
        if (sum2 == BOARD_SIZE_LOGIC) {
            //printf("Found a winning solution for x on / diagonal\n");
            return 10;
        }
        if (sum2 == -BOARD_SIZE_LOGIC) {
            //printf("Found a winning solution for x on / diagonal\n");
            return -10;
        }
        //printf("Sum for \\ diagonal is : %d \n", sum1);
        //printf("Sum for / diagonal is : %d \n", sum2);
    }
    return 0;
}