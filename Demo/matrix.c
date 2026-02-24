#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 9

int grid[N][N];

/* Check if num can be placed at grid[row][col] */
int is_valid(int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) return 0;  // Check row
        if (grid[i][col] == num) return 0;  // Check column
    }
    return 1;
}

/* Shuffle array of size N */
void shuffle(int *array) {
    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

/* Recursive backtracking function */
int fill_grid(int row, int col) {
    if (row == N)
        return 1;

    int next_row = (col == N - 1) ? row + 1 : row;
    int next_col = (col + 1) % N;

    int numbers[N];
    for (int i = 0; i < N; i++)
        numbers[i] = i + 1;

    shuffle(numbers);

    for (int i = 0; i < N; i++) {
        int num = numbers[i];
        if (is_valid(row, col, num)) {
            grid[row][col] = num;

            if (fill_grid(next_row, next_col))
                return 1;

            grid[row][col] = 0;  // Backtrack
        }
    }

    return 0;
}

/* Print grid */
void print_grid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", grid[i][j]);
        printf("\n");
    }
}

int main() {
    srand(time(NULL));  // Seed randomness

    // Initialize grid to 0
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = 0;

    if (fill_grid(0, 0))
        print_grid();
    else
        printf("Failed to generate grid.\n");

    return 0;
}