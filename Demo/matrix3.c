#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 9
#define REMOVE_COUNT 49   // ← changed from 30 to 49

int grid[N][N];

/* Check if placing num at (row,col) is valid */
int is_valid(int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) return 0;
        if (grid[i][col] == num) return 0;
    }

    int box_row = row - row % 3;
    int box_col = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[box_row + i][box_col + j] == num)
                return 0;

    return 1;
}

/* Fisher-Yates shuffle */
void shuffle(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

/* Recursive backtracking fill */
int fill_grid(int row, int col) {
    if (row == N)
        return 1;

    int next_row = (col == N - 1) ? row + 1 : row;
    int next_col = (col + 1) % N;

    if (grid[row][col] != 0)
        return fill_grid(next_row, next_col);

    int numbers[N];
    for (int i = 0; i < N; i++)
        numbers[i] = i + 1;

    shuffle(numbers, N);

    for (int i = 0; i < N; i++) {
        if (is_valid(row, col, numbers[i])) {
            grid[row][col] = numbers[i];

            if (fill_grid(next_row, next_col))
                return 1;

            grid[row][col] = 0;
        }
    }

    return 0;
}

/* Remove random cells */
void remove_cells(int count) {
    int removed = 0;

    while (removed < count) {
        int row = rand() % N;
        int col = rand() % N;

        if (grid[row][col] != 0) {
            grid[row][col] = 0;
            removed++;
        }
    }
}

/* Print Sudoku */
void print_grid() {
    printf("+-------+-------+-------+\n");

    for (int i = 0; i < N; i++) {
        printf("| ");
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0)
                printf(". ");
            else
                printf("%d ", grid[i][j]);

            if ((j + 1) % 3 == 0)
                printf("| ");
        }
        printf("\n");

        if ((i + 1) % 3 == 0)
            printf("+-------+-------+-------+\n");
    }
}

int main() {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = 0;

    if (fill_grid(0, 0)) {
        remove_cells(REMOVE_COUNT);
        print_grid();
    } else {
        printf("Failed to generate Sudoku.\n");
    }

    return 0;
}