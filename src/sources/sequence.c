#include <stdlib.h>
#include <stdio.h>

#include "../headers/sequence.h"

/**
 * TODO: Initializes a sequence, setting the initial values of the structure according to the implementation.
 *
 * Pre:
 * Post: a sequence with initial values first_step and last_step NULL and size 0.
 */
void init_sequence(Sequence* sequence) {
    sequence->first_step = NULL; //every time you initialize a pointer you have to set it as NULL
    sequence->last_step = NULL;
    sequence->size = 0;
}

/**
 * TODO: Adds a step, creating it if needed, as the first step of the sequence.
 *
 * Pre:
 * Post:
 */
void add_step_as_first(Sequence* sequence, int position, int dice_value) {
    Step* step = (Step*)malloc(sizeof(Step));
    //step->next_step = (Step*)malloc(sizeof(Step));
    step->dice_value = dice_value;
    step->resulting_position = position; //not sure
    step->next_step = NULL;
    if(sequence->first_step == NULL){
        sequence->first_step = step;
        sequence->last_step = step;
    } else{
        //sequence->first_step->next_step = step;
        step->next_step = sequence->first_step; //written in class
        sequence->first_step = step; //written in class
    }
    sequence->size++;
}

/**
 * TODO: Adds a step, creating it if needed, as the last step of the sequence.
 *
 * Pre:
 * Post:
 */
void add_step_as_last(Sequence* sequence, int position, int dice_value) {
    Step* step = (Step*)malloc(sizeof(Step));
    step->dice_value = dice_value;
    step->resulting_position = position;
    step->next_step = NULL;
    if(sequence->first_step == NULL){
        sequence->first_step = step;
        sequence->last_step = step;
    }else{
        sequence->last_step->next_step = step;
        sequence->last_step = step;
    }
    sequence->size++;
}


/**
 * TODO: Returns the number of steps stored in the sequence.
 *
 * Pre:
 * Post:
 */
int get_sequence_size(Sequence* sequence) {
    return sequence->size;
    //return 0;
}

/**
 * Deletes (freeing if needed) all the steps stored in the sequence.
 * @param sequence The sequence to be cleared.
 *
 * Pre:
 * Post:
 */
 void clear_sequence(Sequence* sequence) {
     Step* tmp = sequence->first_step;
     while(tmp != NULL){
         sequence->first_step = sequence->first_step->next_step;
         free(tmp);
         tmp=sequence->first_step;
     }
    init_sequence(sequence);
 }


/**
 * Prints the sequence of moves leading to the state.
 * @param sequence The sequence to be shown.
 *
 * Pre:
 * Post:
 */
void print_sequence(Sequence* sequence) {
    Step* tmp = sequence->first_step;
    while(tmp != NULL){
        sequence->first_step = sequence->first_step->next_step;
        //“With a 6, move to square 6”
        printf("With a %d move to square %d\n", tmp->dice_value,tmp->resulting_position);
        tmp=sequence->first_step;
    }
}
