#include "solver.h"

int is_valid_num(int board[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num) return 0;
        if (board[i][col] == num) return 0;
    }

    int box_row = row - row % 3;
    int box_col = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[box_row + i][box_col + j] == num)
                return 0;

    return 1;
}

int solve_board(int board[N][N], int row, int col) {
    if (row == N)
        return 1;

    int next_row = (col == N - 1) ? row + 1 : row;
    int next_col = (col + 1) % N;

    if (board[row][col] != 0)
        return solve_board(board, next_row, next_col);

    for (int num = 1; num <= 9; num++) {
        if (is_valid_num(board, row, col, num)) {
            board[row][col] = num;
            if (solve_board(board, next_row, next_col))
                return 1;
            board[row][col] = 0;
        }
    }
    return 0;
}

int count_solutions(int board[N][N], int row, int col, int *count) {
    if (*count > 1) return 0;

    if (row == N) {
        (*count)++;
        return 0;
    }

    int next_row = (col == N - 1) ? row + 1 : row;
    int next_col = (col + 1) % N;

    if (board[row][col] != 0)
        return count_solutions(board, next_row, next_col, count);

    for (int num = 1; num <= 9; num++) {
        if (is_valid_num(board, row, col, num)) {
            board[row][col] = num;
            count_solutions(board, next_row, next_col, count);
            board[row][col] = 0;
        }
    }
    return 0;
}