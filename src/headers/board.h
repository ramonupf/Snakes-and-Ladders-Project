#ifndef BOARD_H
#define BOARD_H

#include "common.h"
#include "tile.h"

#define MAX_ROWS 10
#define MAX_COLUMNS 10

#define INVALID_BOARD_DIMENSIONS -1

//We define the structure for the board. It should contain the number of rows and columns, as well a 2D array of TILES
typedef struct {
    int rows; //number of rows
    int cols; //number of columns
    Tile tiles[MAX_ROWS][MAX_COLUMNS]; //2D Array of tiles (data type Tile). It doesn't necessarily mean that every game will have these number of tiles. They are the maximum our game will handle
} Board;

int init_board(Board* board, int rows, int columns);

int get_rows(Board* board);
void set_rows(Board* board, int size);

int get_columns(Board* board);
void set_columns(Board* board, int size);

int get_size(Board* board);

Tile* get_tile_at(Board* board, int position);

void free_board(Board* board);

#endif //BOARD_H
