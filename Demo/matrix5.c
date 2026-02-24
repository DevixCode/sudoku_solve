#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define N 9
#define REMOVE_COUNT 49
#define MAX_MISTAKES 3

int grid[N][N];
int solution[N][N];

/* ================= VALID CHECK ================= */

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

/* ================= SHUFFLE ================= */

void shuffle(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

/* ================= GENERATE SOLUTION ================= */

int fill_grid(int board[N][N], int row, int col) {
    if (row == N)
        return 1;

    int next_row = (col == N - 1) ? row + 1 : row;
    int next_col = (col + 1) % N;

    if (board[row][col] != 0)
        return fill_grid(board, next_row, next_col);

    int numbers[N];
    for (int i = 0; i < N; i++)
        numbers[i] = i + 1;

    shuffle(numbers, N);

    for (int i = 0; i < N; i++) {
        if (is_valid_num(board, row, col, numbers[i])) {
            board[row][col] = numbers[i];

            if (fill_grid(board, next_row, next_col))
                return 1;

            board[row][col] = 0;
        }
    }

    return 0;
}

/* ================= SOLUTION COUNTER ================= */

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

/* ================= REMOVE CELLS (UNIQUE SAFE) ================= */

void remove_cells_unique(int count) {
    int attempts = 0;

    while (count > 0 && attempts < 1000) {
        int row = rand() % N;
        int col = rand() % N;

        if (grid[row][col] == 0)
            continue;

        int backup = grid[row][col];
        grid[row][col] = 0;

        int temp[N][N];
        memcpy(temp, grid, sizeof(temp));

        int solution_count = 0;
        count_solutions(temp, 0, 0, &solution_count);

        if (solution_count != 1) {
            grid[row][col] = backup; // revert
            attempts++;
        } else {
            count--;
        }
    }
}

/* ================= PRINT ================= */

void print_grid() {
    printf("\n    A B C   D E F   G H I\n");
    printf("  +-------+-------+-------+\n");

    for (int i = 0; i < N; i++) {
        printf("%d | ", i + 1);

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
            printf("  +-------+-------+-------+\n");
    }
}

int count_empty() {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (grid[i][j] == 0)
                count++;
    return count;
}

/* ================= MAIN ================= */

int main() {
    srand((unsigned int)time(NULL));

    /* Generate full solution */
    memset(grid, 0, sizeof(grid));

    fill_grid(grid, 0, 0);

    memcpy(solution, grid, sizeof(grid));

    remove_cells_unique(REMOVE_COUNT);

    print_grid();

    int mistakes = 0;

    while (count_empty() > 0) {

        char input[20];

        printf("\nEnter (e.g., A5 7) or Q to quit: ");
        scanf("%s", input);

        if (toupper(input[0]) == 'Q') {
            printf("Game exited.\n");
            return 0;
        }

        char col_char = toupper(input[0]);
        int row = input[1] - '0';

        int num;
        scanf("%d", &num);

        int col = col_char - 'A';
        int r = row - 1;

        if (col < 0 || col >= 9 || r < 0 || r >= 9 || num < 1 || num > 9) {
            printf("Invalid input!\n");
            continue;
        }

        if (grid[r][col] != 0) {
            printf("Cell already filled!\n");
            continue;
        }

        if (solution[r][col] == num) {
            grid[r][col] = num;
            printf("Correct!\n");
            print_grid();
        } else {
            mistakes++;
            printf("Wrong! Mistakes: %d/%d\n", mistakes, MAX_MISTAKES);

            if (mistakes >= MAX_MISTAKES) {
                printf("\nGame Over! Too many mistakes.\n");
                return 0;
            }
        }
    }

    printf("\n🎉 Congratulations! You solved the Sudoku!\n");
    return 0;
}