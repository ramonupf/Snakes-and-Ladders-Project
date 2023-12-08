#include <stdio.h>

#include "../headers/state.h"

/**
 * TODO (2nd submission): Initializes the state, setting the playing board, the current position to 0 and finished flag to FALSE.
 *
 * @param state The state to be initialized.
 * @param board The playing board.
 *
 * Pre: A state pointer of data type State and a board pointer of data type Board
 * Post: Initializes the state and sets the state board to the given board.
 */
void init_state(State* state, Board* board) {
    state->current_position = 0;
    state->game_finished = FALSE;
    state->board = *board;
    Sequence sequence;
    init_sequence(&sequence);
    state->state_sequence = sequence;
    //init_sequence(state->state_sequence);
}

/**
 * TODO (2nd submission): Sets the current position.
 *
 * @param state The state to be updated.
 * @param position The current position.
 *
 * Pre: A state pointer of data type State and an integer position
 * Post: Sets the state current_position integer to the given position value
 *
 */
void set_current_position(State* state, int position) {
    state->current_position = position;
}

/**
 * TODO (2nd submission): Retrieves the current position.
 *
 * @param state The state that stores the current position.
 * @return The current position.
 *
 * Pre: A state pointer of data type State
 * Post: Returns the current_position integer value of the state
 */
int get_current_position(State* state) {
    return state->current_position;
}

/**
 * TODO (2nd submission): Sets the finished flag to finished value (TRUE or FALSE)
 *
 * @param state The state to be updated.
 * @param is_finished The value marking the game as finished or not.
 *
 * Pre: A state pointer of data type State and a finished integer value which can be TRUE or FALSE
 * Post: Set the game_finished integer of the given state to the given finished value.
 */
void set_finished(State* state, int finished) {
    state->game_finished = finished;
}

/**
 * TODO (2nd submission): Returns the value of is_finished flag (TRUE or FALSE), marking a game as finished.
 *
 * @param state The state to be updated.
 *
 * Pre: A state pointer of data type State
 * Post: Returns the game_finished integer of the given state
 */
int is_finished(State* state) {
    return state->game_finished;
}

/**
 * TODO: Moves the player a number of steps in the board, updating the state's current position. If the player ends up in a
 * tile containing a ladder or a snake updates the state's current position accordingly. Also, sets the state as
 * finished if it moves to or past the last tile. Returns SNAKE_FOUND or LADDER_FOUND if found, SUCCESS otherwise.
 *
 * @param board The playing board.
 * @param state The current state.
 * @param steps The number of steps to move.
 *
 * Pre:
 * Post:
 */
/**
 * TODO (2nd submission): Moves the player a number of steps in the board, updating the state's current position. If the player ends up in a
 * tile containing a ladder or a snake, prints a message (You found a ladder/snake!) and updates the state's current
 * position accordingly. Also, sets the state as finished if it moves to or past the last tile.
 *
 * @param board The playing board.
 * @param state The current state.
 * @param steps The number of steps to move.
 *
 * Pre: A state pointer of data type State and an integer with the dice value
 * Post: Sets the current_position integer of the state accordingly to the given value.
 *       Prints if a ladder or a snake is found
 *       Checks if the new current_position is a wining move and if it is, sets the game_finished integer to TRUE
 */
int move(State* state, int dice_value) {
    Tile *new_tile;

    int new_position = state->current_position + dice_value;
    new_tile = get_tile_at(&state->board, new_position);
    int final_position = (state->board.rows * state->board.cols)-1;
    if(new_position >= final_position){
        new_position = final_position;
    }
    set_current_position(state,new_position);
    //Check winning move MODIFIED AFTER LAB 2 TO SOLVE BUGS ;)
    if(final_position <= state->current_position){
        set_finished(state, TRUE);
    }
    else if(is_ladder(new_tile)){
        set_current_position(state,new_tile->tar);
        return LADDER_FOUND;
    } else if(is_snake(new_tile)){
        set_current_position(state,new_tile->tar);
        return SNAKE_FOUND;
    }
    return SUCCESS;
}


/**
 * TODO: Adds a step to the state's sequence, as the last step of it.
 *
 * Pre:
 * Post:
 */
void add_step(State* state, int dice_value) {
    add_step_as_last(&state->state_sequence, get_current_position(state),dice_value);
}


/**
 * Prints the sequence of the state.
 * @param sequence The sequence to be shown.
 *
 * Pre:
 * Post:
 */
void print_state_sequence(State* state) {
    print_sequence(&state->state_sequence);
}


/**
 * Clear the state history and init the state again
 * @param state The current state to reset
 *
 * Pre: 
 * Post: 
 */
void reset(State *state){
    clear_sequence(&state->state_sequence);
    init_state(state,&state->board);
}
