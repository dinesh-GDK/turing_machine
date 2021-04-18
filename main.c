#include<stdio.h>
#include<stdlib.h>
#include"card.h"
#include"cell.h"

uint MAX_STEPS = 1000;

void main(int argc, char *argv[]) {

    struct Card *cards_head = get_cards(argv[1]);

    if(validate_cards(cards_head) == 0)
        return;

    print_cards(cards_head);

    struct Cell *tape_head = (struct Cell*)malloc(sizeof(struct Cell));
    tape_head->prev = NULL, tape_head->next = NULL;

    get_initial_tape(tape_head, argv[2]);

    if(validate_tape(tape_head) == 0)
        return;

    print_tape(tape_head);

    printf("------------------------\n\n");
    struct Card *current_card = cards_head->next;

    int idx = 1;
    while(1) {

        if(current_card->id == 0)
            break;

        uint temp_val = tape_head->val;
        tape_head->val = current_card->state[temp_val].write;
        tape_head = move(tape_head, current_card->state[temp_val].move);
        current_card = search_card(cards_head, current_card->state[temp_val].next_card);

        printf("STEP: %d\n", idx);
        print_tape(tape_head);

        idx++;
        if(idx == MAX_STEPS+1) {
            printf("Maximum steps exeeced\n");
            return;
        }
    }

    printf("------------------------\n");
    printf("Result\n");
    print_tape(tape_head);
    printf("Number of ones: %d\n", tape_count_ones(tape_head));
}
