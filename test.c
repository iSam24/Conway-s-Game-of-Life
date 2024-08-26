#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <unistd.h> 
#include <time.h>

#define ROWS 200
#define COLS 100
#define CELL_SIZE 4
#define DELAY 5000000 //(5,000,000 microseconds == 0.5s)

// Screen dimension constants
const int WIDTH = 800, HEIGHT = 600, SCALE = 1;

// Define functions 
void create_grid(int grid[ROWS][COLS]);
void random(int grid[ROWS][COLS], float alive_prob);
void draw(int grid[ROWS][COLS], SDL_Renderer *renderer);
void count_neighbours(int grid[ROWS][COLS], int count_grid[ROWS][COLS]);
void apply_rules(int grid[ROWS][COLS], int count_grid[ROWS][COLS]);


int main (int argc, char *argv[]) {
    printf("Initialising Video");
    SDL_Init(SDL_INIT_VIDEO);

    printf("Creating Window");
    SDL_Window *window = SDL_CreateWindow("The Game Of Life", 
                                            100, 
                                            100, 
                                            WIDTH * SCALE, 
                                            HEIGHT * SCALE, 
                                            SDL_WINDOW_ALLOW_HIGHDPI);
    // Check window is created
    if ( NULL == window)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    printf("Creating Render");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 
                            -1,
                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    printf("Creating Boards");

    SDL_Event windowEvent;

    int grid[ROWS][COLS];
    int count_grid[ROWS][COLS];

    create_grid(grid);
    random(grid, (float)(0.1));
    draw(grid, renderer);

    Uint32 delay = 10; // 500 ms delay
    Uint32 next_time = SDL_GetTicks() + delay;

    while (1)
    {
        count_neighbours(grid, count_grid);
        apply_rules(grid, count_grid);
        draw(grid, renderer);
        if ( SDL_PollEvent (&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            { 
                break; 
            }
        }
            // Wait for the next frame
        Uint32 now = SDL_GetTicks();
        if (next_time > now) {
         SDL_Delay(next_time - now);
        }
        next_time += delay;
    }
    
    SDL_DestroyWindow (window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

// ----------- FUNCTIONS ------------------
void create_grid(int grid[ROWS][COLS]){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            grid[i][j] = 0;
        }
    }
}

void draw(int grid[ROWS][COLS], SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(grid[i][j] == 1) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green for live cells
            }
            else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black for dead cells
            }
            SDL_Rect    cellRect = {j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE };
            SDL_RenderFillRect(renderer, &cellRect);
        }
    }
    SDL_RenderPresent(renderer);
}

void random(int grid[ROWS][COLS], float alive_prob) {
    srand((unsigned int)time(NULL));
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            grid[i][j] = ((float)rand() / RAND_MAX) < alive_prob ? 1:0;
        }
    }
}

void count_neighbours(int grid[ROWS][COLS], int count_grid[ROWS][COLS]) {
    //each cell has 8 neighbors unless on an edge or corner
    //check if cell is center, edge, or corner.
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            int count = 0;
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