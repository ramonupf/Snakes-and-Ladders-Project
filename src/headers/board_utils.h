#ifndef BOARD_UTILS_H
#define BOARD_UTILS_H

#include "board.h"

#define MAX_LOADING_BUFFER 50
#define MAX_ROOM_DATA 10

#define FILE_NOT_FOUND -2
#define INVALID_TILE_LINE -3
#define INVALID_TILE_DATA -4
#define INVALID_TILE_POSITION -6
#define INVALID_TILE_ROLE -7
#define INVALID_TILE_TARGET -8

#define BOLD_BLACK "\e[1;90m"
#define BOLD_YELLOW "\e[1;93m"
#define BOLD_MAGENTA "\e[1;95m"
#define BOLD_CYAN "\e[1;96m"
#define BOLD_WHITE "\e[1;97m"
#define FONT_RED "\e[31m"
#define FONT_BLUE "\e[34m"
#define RESET "\e[0m"

#ifdef __WIN32
#define UPPER_LEFT_CORNER "\xDA"
#define UPPER_RIGHT_CORNER "\xBF"
#define BOTTOM_LEFT_CORNER "\xC0"
#define BOTTOM_RIGHT_CORNER "\xD9"
#define HORIZONTAL_BAR "\xC4\xC4\xC4\xC4"
#define HORIZONTAL_OPEN_BAR "\xC4  \xC4"
#define VERTICAL_BAR "\xB3"
#define VERTICAL_OPEN_BAR " "
#else
#define UPPER_LEFT_CORNER "┏"
#define UPPER_RIGHT_CORNER "┓"
#define BOTTOM_LEFT_CORNER "┗"
#define BOTTOM_RIGHT_CORNER "┛"
#define HORIZONTAL_BAR "━━━━"
#define HORIZONTAL_OPEN_BAR "╸  ╺"
#define VERTICAL_BAR "┃"
#define VERTICAL_OPEN_BAR " "
#endif

#define BOLD BOLD_WHITE

#define INITIAL_PLACEHOLDER "I"
#define CURRENT_PLACEHOLDER "X"
#define FINAL_PLACEHOLDER "F"
#define EMPTY_SPACE " "

void draw_zigzag_board(FILE* fd, Board* board, int current_position);

int init_basic_board(Board* board);

int load_board(Board* board, char* path);

#endif //BOARD_UTILS_H
