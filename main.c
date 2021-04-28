#include<stdio.h>
#include<stdlib.h>
#include"card.h"
#include"cell.h"

// maximum number of shifts done by the program
const uint MAX_STEPS = 10000;

void main(int argc, char *argv[]) {

    struct Card *cards_head = get_cards(argv[1]);
    if(cards_head == NULL) {
        printf("System out of memory");
        exit(0);
    }

    if(validate_cards(cards_head) == 0)
        return;

    print_cards(cards_head);

    struct Cell *tape_head = (struct Cell*)malloc(sizeof(struct Cell));
    if(tape_head == NULL) {
        printf("System out of memory");
        exit(0);
    }
    tape_head->prev = NULL, tape_head->next = NULL;

    get_initial_tape(tape_head, argv[2]);

    if(validate_tape(tape_head) == 0)
        return;

    print_tape(tape_head);

    printf("Starting Execution...\n---------------------\n\n");
    struct Card *current_card = cards_head->next;

    int idx = 0;
    while(1) {

        printf("STEP: %d\n", idx);
        print_tape(tape_head);

        if(current_card->id == 0)
            break;

        uint temp_val = tape_head->val;
        tape_head->val = current_card->state[temp_val].write;
        tape_head = move(tape_head, current_card->state[temp_val].move);
        current_card = search_card(cards_head, current_card->state[temp_val].next_card);

        idx++;
        if(idx == MAX_STEPS+1) {
            printf("Maximum steps exeeced\n");
            return;
        }
    }

    printf("---------------------\nEnd of Execution\n\n");
    printf("Result\n");
    print_tape(tape_head);
    printf("Number of ones: %d\n", tape_count_ones(tape_head));
}
