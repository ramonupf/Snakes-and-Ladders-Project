#include <stdio.h>
#include <string.h>

#include "../headers/board_utils.h"

#define INITIAL_TILE 0
#define MIDDLE_TILE 1
#define LEFT_BOTTOM_TILE 2
#define LEFT_TOP_TILE 3
#define RIGHT_BOTTOM_TILE 4
#define RIGHT_TOP_TILE 5
#define LEFT_FINAL_TILE 6
#define RIGHT_FINAL_TILE 7

typedef struct {
    Tile* tile;
    int type;
    int current;
} BoardTile;

void init_btile(BoardTile* bTile, Tile* tile, int type, int current) {
    bTile->tile = tile;
    bTile->type = type;
    bTile->current = current;
}

Tile* get_tile(BoardTile* bTile) {
    return bTile->tile;
}

int get_type(BoardTile* bTile) {
    return bTile->type;
}

int is_current(BoardTile* bTile) {
    return bTile->current;
}

void draw_top(FILE* fd, BoardTile* bTile) {
    fprintf(fd, "%s", UPPER_LEFT_CORNER);

    int type = get_type(bTile);
    if (type == LEFT_BOTTOM_TILE || type == RIGHT_BOTTOM_TILE) {
        fprintf(fd, HORIZONTAL_OPEN_BAR);
    } else {
        fprintf(fd, "%s", HORIZONTAL_BAR);
    }
    fprintf(fd, "%s", UPPER_RIGHT_CORNER);
}

void draw_middle_top(FILE* fd, BoardTile* bTile) {

    int type = get_type(bTile);
    if (type == INITIAL_TILE || type == LEFT_FINAL_TILE ||
        type == LEFT_BOTTOM_TILE || type == LEFT_TOP_TILE) {
        fprintf(fd, "%s", VERTICAL_BAR);
    } else {
        fprintf(fd, "%s", VERTICAL_OPEN_BAR);
    }

    if (type == INITIAL_TILE) {
        fprintf(fd, "%s%s%s", BOLD, INITIAL_PLACEHOLDER, RESET);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);

    } else if (type == LEFT_FINAL_TILE) {
        fprintf(fd, "%s%s%s", BOLD, FINAL_PLACEHOLDER, RESET);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);

    } else if (type == RIGHT_FINAL_TILE) {
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, "%s%s%s", BOLD, FINAL_PLACEHOLDER, RESET);

    } else {
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, "%2d", get_position(bTile->tile));
    }

    if (type == RIGHT_FINAL_TILE || type == RIGHT_BOTTOM_TILE || type == RIGHT_TOP_TILE) {
        fprintf(fd, "%s", VERTICAL_BAR);
    } else {
        fprintf(fd, "%s", VERTICAL_OPEN_BAR);
    }
}
void draw_middle_bottom(FILE* fd, BoardTile* bTile) {

    int type = get_type(bTile);
    if (type == INITIAL_TILE || type == LEFT_FINAL_TILE ||
        type == LEFT_BOTTOM_TILE || type == LEFT_TOP_TILE) {
        fprintf(fd, "%s", VERTICAL_BAR);
    } else {
        fprintf(fd, "%s", VERTICAL_OPEN_BAR);
    }

    fprintf(fd, EMPTY_SPACE);

    if (is_current(bTile) == TRUE) {
        fprintf(fd, "%s%s%s", BOLD_MAGENTA, CURRENT_PLACEHOLDER, RESET);
    } else {
        fprintf(fd, EMPTY_SPACE);
    }

    Tile* tile = get_tile(bTile);
    if (is_snake(tile)) {
        fprintf(fd, "%s%2d%s", FONT_RED, get_target_position(tile), RESET);
    } else if (is_ladder(tile)) {
        fprintf(fd, "%s%2d%s", FONT_BLUE, get_target_position(tile), RESET);
    } else {
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
    }

    if (type == RIGHT_FINAL_TILE || type == RIGHT_BOTTOM_TILE || type == RIGHT_TOP_TILE) {
        fprintf(fd, "%s", VERTICAL_BAR);
    } else {
        fprintf(fd, "%s", VERTICAL_OPEN_BAR);
    }
}

void draw_bottom(FILE* fd, BoardTile* bTile) {
    fprintf(fd, "%s", BOTTOM_LEFT_CORNER);

    int type = get_type(bTile);
    if (type == LEFT_TOP_TILE || type == RIGHT_TOP_TILE) {
        fprintf(fd, HORIZONTAL_OPEN_BAR);
    } else {
        fprintf(fd, "%s", HORIZONTAL_BAR);
    }

    fprintf(fd, "%s", BOTTOM_RIGHT_CORNER);
}

void draw_tile(FILE* fd, BoardTile* tile, int line) {

    if (line == 0) {
        draw_top(fd, tile);

    } else if (line == 1) {
        draw_middle_top(fd, tile);

    } else if (line == 2) {
        draw_middle_bottom(fd, tile);

    } else if (line == 3) {
        draw_bottom(fd, tile);

    } else {
        // error
    }
}

void draw_board(FILE* fd, BoardTile* matrix, int rows, int columns) {

    for (int idx=0; idx<rows; idx++) {
        for (int line=0; line<4; line++) {
            for (int jdx = 0; jdx < columns; jdx++) {
                BoardTile* tile = &(matrix[idx*columns + jdx]);

                draw_tile(fd, tile, line);
                fprintf(fd, " ");
            }
            fprintf(fd, "\n");
        }
    }
    fprintf(fd, "\n");
}

void draw_zigzag_board(FILE* fd, Board* board, int current_position) {

    int rows = get_rows(board);
    int columns = get_columns(board);
    BoardTile matrix[rows][columns];

    int row = rows-1;
    int column = 0;
    int size = get_size(board);
    for (int idx=0; idx < size; idx++) {
        Tile* tile = get_tile_at(board, idx);
        BoardTile* bTile = &matrix[row][column];

        int type = MIDDLE_TILE;
        if (idx == 0) {
            type = INITIAL_TILE;
            column++;

        } else if (row % 2 == rows % 2) {
            if (idx == size-1) {
                type = LEFT_FINAL_TILE;

            } else if (column == 0) {
                row--;
                type = LEFT_BOTTOM_TILE;

            } else {
                if (column == columns-1) {
                    type = RIGHT_TOP_TILE;
                }
                column--;
            }
        } else {
            if (idx == size-1) {
                type = RIGHT_FINAL_TILE;

            } else if (column == columns-1) {
                row--;
                type = RIGHT_BOTTOM_TILE;
            } else {
                if (column == 0) {
                    type = LEFT_TOP_TILE;
                }
                column++;
            }
        }

        int current;
        if (idx == current_position) {
            current = TRUE;
        } else {
            current = FALSE;
        }

        init_btile(bTile, tile, type, current);
    }
    draw_board(fd, (BoardTile *) matrix, rows, columns);
}

/**
 * Creates a plain board of 9 tiles (including initial and final) with a ladder in the 2nd tile to the 5th tile
 * and a snake in the 7th tile to the 3rd tile.
 *
 * @param board Board structure to be initialized.
 * @return SUCCESS if the board was initialized properly, ERROR if the size is incorrect.
 */
int init_basic_board(Board* board) {

    int status = init_board(board, 3, 3);
    if (status == SUCCESS) {

        int size = get_size(board);
        for (int idx = 0; idx < size; idx++) {
            Tile* tile = get_tile_at(board, idx);
            if (idx == 2) {
                set_target_position(tile, 5);
            } else if (idx == 7) {
                set_target_position(tile, 3);
            }
        }
    }
    return status;
}


/**
 * TODO (2nd submission): Checks if the input values are valid tile values.
 * @param position The tile position.
 * @param type The tile type (snake or ladder).
 * @param target The target position.
 * @param board_size The size of the board.
 * @return SUCCESS if all the input values are valid, INVALID_TILE_DATA otherwise.
 */
int check_tile_data(int position, char type, int target, int board_size) {
    if(position>0 && position<board_size && target>=0 && target != position){
        if(type == 'S'){
            if(target<position){
                return SUCCESS;
            }
        } else if(type == 'L'){
            if(target>position){
                return SUCCESS;
            }
        } else{
            return INVALID_TILE_DATA;
        }
    } else{
        return INVALID_TILE_DATA;
    }
    return INVALID_TILE_DATA;
}

/**
 * TODO (2nd submission): Reads a tile line from an opened board file, checking its values and configuring the board accordingly.
 * @param board The board to be configured.
 * @param fd The opened board file.
 * @return The status of the action:
 *      - SUCCESS if the file was loaded successfully.
 *      - INVALID_TILE_LINE if an invalid tile line is found.
 *      - INVALID_TILE_DATA if an invalid tile data is found (wrong format, invalid values, etc.)
 */
int read_tile_line(Board* board, FILE* fd) {
    // read line-> position -> tile* = get_tile_at(board,position)-> set_target_position (tile, target read)
    int position = 0;
    int target = 0;
    int check_status;
    char type = ' ';
    Tile* tile;
    int board_size = board->cols * board->rows;
    int scan_code = fscanf(fd, "%d%c%d",&position, &type, &target);
    if(scan_code == 3){
        check_status = check_tile_data(position,type,target,board_size);
        if(check_status == SUCCESS){
            tile = get_tile_at(board, position);
            set_target_position(tile, target);
        }
        return check_status; //SUCCESS
    }else if ( scan_code != EOF) {
        return INVALID_TILE_LINE;
    }
    else{
        return EOF;
    }
}

/**
 * TODO (2nd submission): Reads an opened board file, reading the dimensions line and each of the tile lines, configuring the
 * board accordingly.
 * @param board The board to be configured.
 * @param fd The opened board file.
 * @return The status of the action:
 *      - SUCCESS if the file was loaded successfully.
 *      - INVALID_BOARD_DIMENSIONS if the board dimensions are invalid (wrong format, invalid values, etc.)
 *      - INVALID_TILE_LINE if an invalid tile line is found.
 *      - INVALID_TILE_DATA if an invalid tile data is found (wrong format, invalid values, etc.)
 */
int read_board_file(Board* board, FILE* fd) {
    int rows = 0;
    int columns = 0;
    char type = ' ';
    int scan_code = fscanf(fd, "%d%c%d", &rows, &type, &columns);
    if (scan_code == 3 && rows >0 && rows <= MAX_ROWS && columns>0 && columns <= MAX_COLUMNS && type == 'x') {
        set_rows(board, rows);
        set_columns(board,columns);
        init_board(board, rows, columns);
    } else {
        return INVALID_BOARD_DIMENSIONS;
    }
    scan_code = read_tile_line(board,fd);
    while(scan_code==SUCCESS){
        scan_code = read_tile_line(board, fd);
    }
    if(scan_code == EOF){
        return SUCCESS;
    } else {
        return INVALID_TILE_DATA;
    }
}

/**
 * @param board The board to be initialized with the contents of the file in path.
 * @param path The path to the file containing a board configuration encoded as a text file.
 * @return
 *
 * Pre: board is not NULL
 * Post: returns ERROR if the path is not valid; otherwise it returns the result of reading the board file
 */
int load_board(Board* board, char* path) {
    FILE* fd = fopen(path, "r");
    return read_board_file(board, fd);
}

