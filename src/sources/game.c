#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../headers/game.h"
#include "../headers/utils.h"
#include "../headers/state.h"
#include "../headers/board_utils.h"

#define MAX_ITERATIONS 1000

char show_game_options() {

    char option = read_char_option("Press T for throwing the dice, S for showing the history, Q for quit\n");
    return option;
}

int throw_dice() {
    int value = (rand() % 6) + 1;

    printf("Dice roll... %d!\n", value);

    return value;
}

void start_game(Board *board) {

    State state;
    init_state(&state, board);

    int quit = FALSE;
    printf("Starting game...\n\n");
    while (quit == FALSE) {

        int current_position = get_current_position(&state);

        draw_zigzag_board(stdout, board, current_position);
        char option = show_game_options();

        if (option == THROW_DICE || option == 't') {
            int dice_value = throw_dice();

            int move_status = move(&state, dice_value);
            if (move_status == SNAKE_FOUND) {
                printf("You found a snake... :(\n");

            } else if (move_status == LADDER_FOUND) {
                printf("You found a ladder! :D\n");
            }

            if (is_finished(&state) == TRUE) {
                quit = TRUE;
            }
            add_step(&state, dice_value);

        } else if (option == SHOW_SEQUENCE || option == 's') {
            printf("Steps:\n");
            print_state_sequence(&state);

        } else if (option == QUIT || option == 'q') {
            quit = TRUE;

        } else {
            printf("Invalid option! Try again...\n");
        }
    }

    if (is_finished(&state) == TRUE) {
        int current_position = get_current_position(&state);
        draw_zigzag_board(stdout, board, current_position);
        printf("You won!\n");
    }

    reset(&state);
}


Sequence* try_dice_values(State state, int count, int max_depth);

/**
 * TODO: First, checks if the step count reached the max_depth. If so, returns NULL. If there is room for more steps,
 * does a move (calling move function which updates the state), checking the result. If the finish tile was reached by
 * this movement, creates a sequence, initializing it. If it doesn't, calls try_dice_values to continue searching. This
 * call should return the shortest sequence or NULL. Finally, the step should be added to the sequence, if there is one.
 *
 * @param state The state to move from.
 * @param count The number of steps taken already.
 * @param max_depth The maximum depth allowed.
 *
 * Pre:
 * Post:
 */
Sequence* do_recursive_move(State state, int dice_value, int count, int max_depth) {
    if (count >= max_depth || count*max_depth>=MAX_ITERATIONS) {  //Base case: Maximum depth reached
        return NULL;
    }
    count++;  //increases the count in each recursive move
    move(&state, dice_value);
    if (is_finished(&state) == TRUE) {
        Sequence *sequence = (Sequence *) malloc(sizeof(Sequence));
        init_sequence(sequence);
        add_step_as_first(sequence, get_current_position(&state), dice_value);
        return sequence;
    } else {
        Sequence *shortest_sequence = try_dice_values(state, count, max_depth);
        if (shortest_sequence != NULL) {
            add_step_as_first(shortest_sequence, get_current_position(&state), dice_value);
        }
        return shortest_sequence;
    }
}


/**
 * TODO: Given a state, checks the sequence of steps following a dice value by calling do_recursive_move with each dice
 * value. For each resulting sequence, it returns the shortest one.
 *
 * @param state The state to move from.
 * @param count The number of steps taken already.
 * @param max_depth The maximum depth allowed.
 *
 * Pre:
 *
 * Post:
 */
Sequence* try_dice_values(State state, int count, int max_depth) {
    Sequence* shortest_sequence = NULL;
    count++;
    for (int d = 6; d > 0; d--){
        count++;
        if(is_snake(get_tile_at(&state.board,state.current_position+d))==FALSE){ //This avoids problems with snakes
            Sequence *tmp = do_recursive_move(state, d, count, max_depth);
            if (tmp != NULL) {
                if (shortest_sequence == NULL){
                    shortest_sequence = tmp;
                } else if (shortest_sequence->size >= tmp->size) { //this could be either >= or =
                    clear_sequence(shortest_sequence);
                    free(shortest_sequence);
                    shortest_sequence = tmp;
                } else {
                    clear_sequence(tmp);
                    free(tmp);
                }
            }
        }
    }
    return shortest_sequence;
}
/**
 * TODO: Explores the different sequences of dice values that leads to the finish tile, printing the best one, if any.
 * Uses the size of the board to limit the number of steps explored, it is, the board will be considered unsolvable if
 * no sequence is found under that number of steps.
 *
 * @param board The playing board.
 *
 * Pre:
 * Post:
 */
void solve(Board *board) {
    State state;
    init_state(&state, board);
    int max_depth = get_size(board);
    int count = 0;
    Sequence *sequence = try_dice_values(state, count, max_depth);
    int game_solved = FALSE;
    if (sequence != NULL) {
        printf("Found a solution with %d steps:\n", sequence->size);
        print_sequence(sequence);
        printf("Square %d was the final square! This is the winning move.", sequence->last_step->resulting_position);
        game_solved = TRUE;
    }
    if (game_solved == FALSE) {
        printf("No solution found! (max depth: %d)\nYou can try to increase MAX_ITERATIONS, but maybe you'll need a more powerful computer.", max_depth);
    }
    reset(&state);
}

