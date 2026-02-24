#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "game.h"
#include "generator.h"

#define MAX_MISTAKES 3

static int grid[N][N];
static int solution[N][N];

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

void start_game(int remove_count) {

    generate_full_solution(grid);
    memcpy(solution, grid, sizeof(grid));
    remove_cells_unique(grid, remove_count);

    print_grid();

    int mistakes = 0;

    while (count_empty() > 0) {
        char input[20];

        printf("\nEnter (A5, Q7): ");
        scanf("%s", input);

        if (toupper(input[0]) == 'Q')
            return;

        char col_char = toupper(input[0]);
        int row = input[1] - '0';
        int num;
        scanf("%d", &num);

        int col = col_char - 'A';
        int r = row - 1;

        if (grid[r][col] != 0) {
            printf("Cell already filled!\n");
            continue;
        }

        if (solution[r][col] == num) {
            grid[r][col] = num;
            print_grid();
        } else {
            mistakes++;
            printf("Wrong! %d/%d\n", mistakes, MAX_MISTAKES);
            if (mistakes >= MAX_MISTAKES) {
                printf("Game Over!\n");
                return;
            }
        }
    }

    printf("You solved it!\n");
}