#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BOARD_SIZE_LOGIC 3

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct Move {
    int row;
    int col;
} Move;

typedef struct Score {
    int depth;
    int score;
    int tie;
} Score;

int check_Board_Score(int board[BOARD_SIZE_LOGIC][BOARD_SIZE_LOGIC]);
int check_Moves_Left(int board[BOARD_SIZE_LOGIC][BOARD_SIZE_LOGIC]);
void print_Board(int board[BOARD_SIZE_LOGIC][BOARD_SIZE_LOGIC]);
Move calculate_Best_Move(int board[BOARD_SIZE_LOGIC][BOARD_SIZE_LOGIC]);
Score minimax(int board[BOARD_SIZE_LOGIC][BOARD_SIZE_LOGIC], int depth, int turn);
void show_Best_Move(int board[BOARD_SIZE_LOGIC][BOARD_SIZE_LOGIC], Move best_move);