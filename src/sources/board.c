#include <stdlib.h>

#include "../headers/board.h"

/**
 * TODO (2nd submission): Initializes the board, initializing also each tile of it.
 * @param board The board to be initialized.
 * @param rows The number of rows of the board.
 * @param columns The number of columns of the board.
 * @return SUCCESS code if the initialization was successful, ERROR code if rows are less than 1 or more than MAX_ROWS
 * or if columns is less than 2 or more than MAX_COLUMNS.
 *
 * Pre: A board of data type Board and 2 integers specifying the desired number of rows and columns.
 *      rows have to be at least 1 and less or equal than MAX_ROWS
 *      columns have to be at least 2 and less or equal than MAX_COLUMNS
 * Post: It initializes the board with the required dimensions
 */

int init_board(Board* board, int rows, int columns) {
    if((rows<-1 )|| (rows>MAX_ROWS) || (columns<2 )|| (columns>MAX_COLUMNS)){
        return INVALID_BOARD_DIMENSIONS;
    }
    board->rows = rows;
    board->cols = columns;
    //We call the function of tiles with for loop
    int pos=0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            init_tile(&board->tiles[i][j],pos);
            pos++;
        }
    }
    return SUCCESS;
}

/**
 * TODO (2nd submission): Returns the number of rows of the board.
 * @param board The board to be queried.
 * @return The number of rows of the board.
 *
 * Pre: A valid board pointer of data type Board
 * Post: Returns rows integer of the given board
 */
int get_rows(Board* board) {
    return board->rows;
}

/**
 * TODO (2nd submission): Sets the number of rows of the board.
 * @param board The board to be queried.
 *
 * Pre: A board structure and an integer with the rows.
 * Post: The board structure with the desired rows.
 */
void set_rows(Board* board, int rows) {
    board->rows = rows;
}

/**
 * TODO (2nd submission): Returns the number of columns of the board.
 * @param board The board to be queried.
 * @return The number of columns of the board.
 *
 * Pre: A valid board pointer of data type Board
 * Post: Returns an integer with the columns of the board
 */
int get_columns(Board* board) {
    return board->cols;
}

/**
 * TODO (2nd submission): Sets the number of columns of the board.
 * @param board The board to be queried.
 *
 * Pre: A valid board pointer of data type Board and an integer with a valid number of columns
 * Post: Sets cols in board to the given number of columns value
 */
void set_columns(Board* board, int columns) {
    board->cols = columns;
}

/**
 * TODO (2nd submission): Returns the size of the board, it is, the total number of tiles.
 * @param board The board to be queried.
 * @return The size of the board.
 *
 * Pre: A valid board pointer of data type Board
 * Post: Returns the board size computed from the multiplication of the number of rows and columns of the given board.
 */
int get_size(Board* board) {
    int board_size;
    board_size = board->cols * board->rows;
    return(board_size); //Quality code
}

/**
 * TODO (2nd submission): Returns the board tile at the specific position.
 *
 * @param board The board from which the tile should be retrieved.
 * @param position The position of the tile.
 * @return The (reference to the) tile of the board corresponding to the position if valid, NULL otherwise.
 *
 * Pre: A valid board pointer of data type Board and an integer with a valid position
 * Post: Returns a tile with the corresponding row and column coordinates from the given position.
 */
Tile* get_tile_at(Board *board, int position) {
    int columns = board->cols;
    int row_pos = position / columns;
    int col_pos = position % columns;
    return &board->tiles[row_pos][col_pos];
}