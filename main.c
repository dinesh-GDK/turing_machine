#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"
#include "cell.h"

// default maximum number of shifts done by the program
const uint DEFAULT_MAX_STEPS = 10000;

void print_usage(char *program_name) {
    printf("Usage: %s [options]\n\n", program_name);
    printf("Options:\n");
    printf("  -c, --cards <file>       Path to instruction cards file (required)\n");
    printf("  -t, --tape <file>        Path to initial tape file (required)\n");
    printf("  -m, --max-steps <num>    Maximum steps before halting (default: 10000)\n");
    printf("  -p, --print-steps        Print tape at each step\n");
    printf("  -h, --help               Show this help message\n\n");
    printf("Example:\n");
    printf("  %s -c cards/bb3.txt -t tapes/bb.txt\n", program_name);
    printf("  %s -c cards/bb3.txt -t tapes/bb.txt -m 50000 -p\n", program_name);
}

void main(int argc, char *argv[]) {

    char *cards_file = NULL;
    char *tape_file = NULL;
    uint max_steps = DEFAULT_MAX_STEPS;
    uint print_steps = 0;

    // Parse command line arguments
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--cards") == 0) {
            if(i + 1 < argc) {
                cards_file = argv[++i];
            } else {
                printf("Error: %s requires a file path\n", argv[i]);
                return;
            }
        } else if(strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--tape") == 0) {
            if(i + 1 < argc) {
                tape_file = argv[++i];
            } else {
                printf("Error: %s requires a file path\n", argv[i]);
                return;
            }
        } else if(strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--max-steps") == 0) {
            if(i + 1 < argc) {
                max_steps = atoi(argv[++i]);
            } else {
                printf("Error: %s requires a number\n", argv[i]);
                return;
            }
        } else if(strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--print-steps") == 0) {
            print_steps = 1;
        } else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return;
        } else {
            printf("Error: Unknown option '%s'\n\n", argv[i]);
            print_usage(argv[0]);
            return;
        }
    }

    // Validate required arguments
    if(cards_file == NULL || tape_file == NULL) {
        printf("Error: Both --cards and --tape are required\n\n");
        print_usage(argv[0]);
        return;
    }

    struct Card *cards_head = get_cards(cards_file);
    if(cards_head == NULL) {
        printf("System out of memory");
        exit(0);
    }

    if(validate_cards(cards_head) == 0) {
        free_cards(cards_head);
        return;
    }

    print_cards(cards_head);

    struct Cell *tape_head = (struct Cell*)malloc(sizeof(struct Cell));
    if(tape_head == NULL) {
        printf("System out of memory");
        exit(0);
    }
    tape_head->prev = NULL, tape_head->next = NULL;

    get_initial_tape(tape_head, tape_file);

    if(validate_tape(tape_head) == 0) {
        free_cards(cards_head);
        free_tape(tape_head);
        return;
    }

    print_tape(tape_head);

    printf("Starting Execution...\n---------------------\n\n");
    struct Card *current_card = cards_head->next;

    int idx = 0;
    while(1) {

        if(print_steps) {
            printf("STEP: %d\n", idx);
            print_tape(tape_head);
        }

        if(current_card->id == 0)
            break;

        uint temp_val = tape_head->val;
        tape_head->val = current_card->state[temp_val].write;
        tape_head = move(tape_head, current_card->state[temp_val].move);
        current_card = search_card(cards_head, current_card->state[temp_val].next_card);

        idx++;
        if(idx == max_steps+1) {
            printf("Maximum steps exceeded\n");
            free_cards(cards_head);
            free_tape(tape_head);
            return;
        }
    }

    printf("---------------------\nEnd of Execution\n\n");
    printf("Result\n");
    if(print_steps) print_tape(tape_head);
    printf("Number of ones: %d\n", tape_count_ones(tape_head));

    free_cards(cards_head);
    free_tape(tape_head);
}
