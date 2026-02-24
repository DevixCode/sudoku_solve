#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 9

int grid[N][N];

/* Check if a number can be placed */
int is_valid(int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) return 0;   // Row check
        if (grid[i][col] == num) return 0;   // Column check
    }

    int box_row = row - row % 3;
    int box_col = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[box_row + i][box_col + j] == num)
                return 0;

    return 1;
}

/* Fisher–Yates shuffle */
void shuffle(int arr[]) {
    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

/* Recursive backtracking solver */
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

    shuffle(numbers);

    for (int i = 0; i < N; i++) {
        if (is_valid(row, col, numbers[i])) {
            grid[row][col] = numbers[i];

            if (fill_grid(next_row, next_col))
                return 1;

            grid[row][col] = 0; // backtrack
        }
    }

    return 0;
}

/* Print Sudoku in boxed format */
void print_grid() {
    printf("+-------+-------+-------+\n");

    for (int i = 0; i < N; i++) {
        printf("| ");

        for (int j = 0; j < N; j++) {
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

    // Initialize grid to 0
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = 0;

    if (fill_grid(0, 0))
        print_grid();
    else
        printf("Failed to generate Sudoku grid.\n");

    return 0;
}