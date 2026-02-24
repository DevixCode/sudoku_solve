#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "generator.h"
#include "solver.h"

void shuffle(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int fill_random(int board[N][N], int row, int col) {
    if (row == N)
        return 1;

    int next_row = (col == N - 1) ? row + 1 : row;
    int next_col = (col + 1) % N;

    if (board[row][col] != 0)
        return fill_random(board, next_row, next_col);

    int numbers[N];
    for (int i = 0; i < N; i++)
        numbers[i] = i + 1;

    shuffle(numbers, N);

    for (int i = 0; i < N; i++) {
        if (is_valid_num(board, row, col, numbers[i])) {
            board[row][col] = numbers[i];
            if (fill_random(board, next_row, next_col))
                return 1;
            board[row][col] = 0;
        }
    }
    return 0;
}

void generate_full_solution(int board[N][N]) {
    memset(board, 0, sizeof(int) * N * N);
    fill_random(board, 0, 0);
}

void remove_cells_unique(int board[N][N], int remove_count) {
    int attempts = 0;

    while (remove_count > 0 && attempts < 1000) {
        int row = rand() % N;
        int col = rand() % N;

        if (board[row][col] == 0)
            continue;

        int backup = board[row][col];
        board[row][col] = 0;

        int temp[N][N];
        memcpy(temp, board, sizeof(temp));

        int count = 0;
        count_solutions(temp, 0, 0, &count);

        if (count != 1) {
            board[row][col] = backup;
            attempts++;
        } else {
            remove_count--;
        }
    }
}