#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For usleep function

#define ROWS 20
#define COLS 20

void initialize_grid(int grid[ROWS][COLS]);
void print_grid(int grid[ROWS][COLS]);
void update_grid(int current[ROWS][COLS], int next[ROWS][COLS]);
int count_neighbors(int grid[ROWS][COLS], int x, int y);

int main() {
    int current[ROWS][COLS] = {0};
    int next[ROWS][COLS] = {0};

    initialize_grid(current);

    while (1) {
        print_grid(current);
        update_grid(current, next);
        copy_grid(next, current);
        usleep(200000);  // Sleep for 200 milliseconds
    }

    return 0;
}

// Function Definitions:
// 1. initialize_grid
// 2. print_grid
// 3. update_grid
// 4. count_neighbors
// 5. copy_grid (helper function to copy grid states)

