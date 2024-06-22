# Conway's Game of Life

Conway's Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. The game starts with a grid of cells, each cell can either be alive or dead, and evolves based on a set of rules.

![Game of Life Demo](game_of_life_demo.gif)

## Table of Contents

- [Introduction](#introduction)
- [Rules](#rules)
- [Implementation](#implementation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Conway's Game of Life operates on a grid of cells, each of which can be in one of two states: alive or dead. The game evolves through generations, where each cell's state in the next generation is determined by a set of rules based on its current state and the state of its neighbours.

## Rules

The rules of Conway's Game of Life are straightforward:
1. **Underpopulation**: A live cell with fewer than two live neighbours dies.
2. **Survival**: A live cell with two or three live neighbours remains alive.
3. **Overpopulation**: A live cell with more than three live neighbours dies.
4. **Reproduction**: A dead cell with exactly three live neighbours becomes alive.

These rules create intricate patterns and behaviors from simple initial configurations.

## Implementation

This implementation of Conway's Game of Life is written in C, utilising a 2D array to represent the grid of cells. It includes functions to initialise the grid, randomly populate it, calculate the number of live neighbours for each cell, apply the rules to update the grid, and print the grid for visualisation.

## Usage

1. **Prerequisites**: Ensure you have a C compiler installed (e.g., GCC).

2. **Installation**: Clone the repository and compile the program.

```bash
git clone https://github.com/iSam24/Conway-s-Game-of-Life.git
cd Conway-s-Game-of-Life
gcc game.c -o game