#ifndef TILE_H
#define TILE_H

#include "common.h"

#define EMPTY_TARGET -1

// Definition of the Tile Structure: it should contain its position and the target
typedef struct{
    int pos; //Position of the Tile
    int tar; //Target position. (To which the player is moved)
} Tile;


void init_tile(Tile* tile, int position);

int get_position(Tile* tile);

int get_target_position(Tile* tile);
int set_target_position(Tile* tile, int target_position);

int is_ladder(Tile* tile);
int is_snake(Tile* tile);

#endif //TILE_H
