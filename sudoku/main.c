#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main() {
    srand((unsigned int)time(NULL));

    int choice;

    printf("Select difficulty:\n");
    printf("1. Easy\n2. Medium\n3. Hard\nChoice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: start_game(30); break;
        case 2: start_game(40); break;
        case 3: start_game(50); break;
        default: start_game(40);
    }

    return 0;
}