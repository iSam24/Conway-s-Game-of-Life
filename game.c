#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <time.h>

#define ROWS 40
#define COLS 60 
#define DELAY 1000000 //(5000,000 microseconds == 0.5s)

void create_grid(int grid[ROWS][COLS]);
void print_grid(int grid[ROWS][COLS]);
void random_create(int grid[ROWS][COLS], float alive_prob);
void count_neighbours(int grid[ROWS][COLS], int count_grid[ROWS][COLS]);
void apply_rules(int grid[ROWS][COLS], int count_grid[ROWS][COLS]);

int main() {
    int grid[ROWS][COLS];
    int count_grid[ROWS][COLS];

    create_grid(grid);

    random_create(grid, (float)(0.2));

    print_grid(grid);

    for(int i = 0; i < 20; i++) {
    count_neighbours(grid, count_grid);
    apply_rules(grid, count_grid);
    print_grid(grid);
    usleep(DELAY);

    }

    return 0;

}

//init all grid cells to 0
void create_grid(int grid[ROWS][COLS]){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            grid[i][j] = 0;
        }
    }
}

void print_grid(int grid[ROWS][COLS]){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            if(grid[i][j] == 1) {
                printf("\033[32m█\033[0m "); // Green for live cells
            } else {
                printf("\033[37m·\033[0m "); // White for dead cells
            }
        }
        printf("\n");
    }
    printf("\n");
}

void random_create(int grid[ROWS][COLS], float alive_prob) {
    srand((unsigned int)time(NULL));
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            grid[i][j] = ((float)rand() / RAND_MAX) < alive_prob ? 1:0;
        }
    }
}

//functions needed

//1: count_neighbors

void count_neighbours(int grid[ROWS][COLS], int count_grid[ROWS][COLS]) {
    //each cell has 8 neighbors unless on an edge or corner
    //first step is to check if cell is center, edge, or corner.
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            int count = 0;
            //count = grid[i+1][j] + grid[i+1][j-1] + grid[i+1][j+1] + grid[i][j-1] + grid[i][j+1] + grid[i-1][j] + grid[i-1][j-1] + grid[i-1][j+1]; 
            //check all 8 location 
            for(int xi = -1; xi <= 1; xi++){
                for(int xj = -1; xj <=1; xj++) {
                    //skip if looking at target cell
                    if(xi == 0 && xj == 0) {
                        continue;
                    }
                    int ni = i + xi;
                    int nj = j + xj;

                    //check boundary conditions
                    if(ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS){ 
                        count = count + grid[ni][nj];
                    }
        
                }
            }
            count_grid[i][j] = count;
            //printf("%d ", count_grid[i][j]);
        }
        //printf("\n");

    }
}

//2: apply_rules

void apply_rules(int grid[ROWS][COLS], int count_grid[ROWS][COLS]) {
    for(int i = 0; i <  ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            //if a cell has less than two live neighbors it dies
            if(count_grid[i][j] < 2) {
                grid[i][j] = 0;
            }
            //if a cell has more than three live neighbors it dies (overpopulation).
            else if(count_grid[i][j] > 3) {
                grid[i][j] = 0;
            }
            //A dead cell with exactly three live neighbors becomes a live cell (reproduction).
            else if(grid[i][j] == 0 && count_grid[i][j] == 3) {
                grid[i][j] = 1;
            }
            //if a cell has two or three live neighbors it lives to the next generation
            else if(grid[i][j] == 1 && (count_grid[i][j] == 2 || count_grid[i][j] == 3)) {
                grid[i][j] = 1;
            }
        }
    }
}