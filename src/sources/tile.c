#include "../headers/tile.h"

/**
 * TODO (2nd submission): Initializes a tile, setting the position and initializing the target to EMPTY_TARGET.
 * @param tile The tile to be initialized.
 * @param position The position of the tile.
 *
 * Pre: A tile of data type Tile and a positive integer for the position
 * Post: It initializes a Tile with a position and a Target
 */
void init_tile(Tile* tile, int position)   {
    tile->pos = position;
    tile->tar = EMPTY_TARGET;
}

/**
 * TODO (2nd submission): Returns the position of the tile.
 * @param tile The tile to be queried.
 * @return The position of the tile.
 *
 * Pre: An initialized tile with a position
 * Post: Returns integer with the position of the corresponding tile
 */
int get_position(Tile* tile) {
    if (tile == NULL) {//if the Tile doesn't exist, it needs to return an error.
        return ERROR;
    }
    return (tile->pos); //returns the position of the tile
}

/**
 * TODO (2nd submission): Returns the position the tile targets to, if any.
 * @param tile The tile to be queried.
 * @return The position the tile targets or EMPTY_TARGET, if does not target another tile.
 *
 * Pre: There needs to be a tile with a valid target
 * Post: Returns an integer with the target of the tile or EMPTY_TARGET if there is no target
 */
int get_target_position(Tile* tile) {
    if(tile->tar==EMPTY_TARGET) {//if the Tile doesn't exist, it needs to return an error.
        return EMPTY_TARGET;
    }
    return(tile->tar); //Returns the target of the tile
}

/**
 * TODO (2nd submission): Sets the position the tile targets to.
 * @param tile The tile to be modified.
 * @return INVALID_POSITION if the target_position is less than 0, SUCCESS otherwise.
 *
 * Pre: A tile of data type Tile and an integer target_position
 * Post: Sets the given target position to the given tile
 */


int set_target_position(Tile* tile, int target_position) {
    if((target_position < 0)){ //REVISAR
        return INVALID_POSITION;
    }
    tile->tar = target_position;
    return SUCCESS;
}

/**
 * TODO (2nd submission): Clears the tile target position, setting its value to EMPTY_TARGET.
 * @param tile The tile to be modified.
 *
 * Pre: A tile of data type Tile
 * Post: The target of the input tile is now EMPTY_TARGET
 */
void clear_target_position(Tile* tile) {
    tile->tar = EMPTY_TARGET;
}

/**
 * TODO (2nd submission): Returns TRUE if the tile contains a ladder (targets a higher tile).
 * @param tile The tile to be queried.
 * @return TRUE if the tile contains a ladder.
 *
 * Pre: A tile of data type Tile
 * Post: It will return TRUE if the tile contains a ladder, FALSE otherwise.
 */
int is_ladder(Tile* tile) {
    if(tile->tar > tile->pos){ //pos+1 to check if it is a ladder
        return TRUE;
    } else{
        return FALSE;
    }
}

/**
 * TODO (2nd submission): Returns TRUE if the tile contains a snake (targets a lower tile), FALSE otherwise.
 * @param tile The tile to be queried.
 * @return TRUE if the tile contains a snake, FALSE otherwise.
 *
 * Pre: A tile of data type Tile
 * Post: The function will return TRUE if the tile contains a snake, and false otherwise
 */
int is_snake(Tile* tile) {
    if((tile->tar != EMPTY_TARGET) && (tile->tar < tile->pos)){
        return TRUE;
    } else{
        return FALSE;
    }
}