#ifndef SOLVER_H
#define SOLVER_H

#define N 9

int is_valid_num(int board[N][N], int row, int col, int num);
int solve_board(int board[N][N], int row, int col);
int count_solutions(int board[N][N], int row, int col, int *count);

#endif