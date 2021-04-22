#include<stdio.h>

struct State {
    uint write;
    char move;
    uint next_card;
};

struct Card {
    uint id;
    struct State state[2];
    struct Card *next; 
};

struct Card *get_cards(char *file) {
    /*
    Collects the data for the instruction cards from the file and creates a
    singly linked list

    args:
        file - path to the file which has the data in the specified format
    
    ret:
        head - pointer to the first instruction card
    */

    FILE *fptr = fopen(file, "r");
    if(fptr == NULL) {
        printf("Error reading file\n");
        exit(0);
    }
    
    // creating the hault card
    struct Card *head = (struct Card*)malloc(sizeof(struct Card));
    if(head == NULL) {
        printf("System out of memory");
        exit(0);
    }
    head->id = 0;
    head->state[0].write = 0, head->state[0].move = 'S', head->state[0].next_card = 0;
    head->state[1].write = 0, head->state[1].move = 'S', head->state[1].next_card = 0;

    head->next = (struct Card*)malloc(sizeof(struct Card));
    if(head->next == NULL) {
        printf("System out of memory");
        exit(0);
    }
    struct Card *dummy = head->next, *prev;

    while(fscanf(fptr, "%d", &dummy->id) != EOF) {
        
        fscanf(fptr, "%d %c %d", &dummy->state[0].write, &dummy->state[0].move, &dummy->state[0].next_card);
        fscanf(fptr, "%d %c %d", &dummy->state[1].write, &dummy->state[1].move, &dummy->state[1].next_card);

        dummy->next = (struct Card*)malloc(sizeof(struct Card));
        if(dummy == NULL) {
            printf("System out of memory");
            exit(0);
        }
        prev = dummy;
        dummy = dummy->next;
    }

    prev->next = NULL;
    free(dummy);
    fclose(fptr);
    
    return head;
}

struct Card *search_card(struct Card* head, uint target) {
    /*
    Searches the singly linked list of cards to get the card with the target
    value as id

    args:
        head - pointer to the head of the singly linked list of cards
        target - id value of the card to find
    
    ret:
        if the card exists returns the pointer to the card
        else it returns 'NULL'
    */

    struct Card *dummy = head;

    while(dummy != NULL) {

        if(dummy->id == target)
            return dummy;
        dummy = dummy->next;
    }

    return NULL;
}

uint find_duplicacy(struct Card *head, uint target) {
    /*
    Searches the singly linked list for duplicacy with the target id
    args:
        head - the head of the singly linked lists of cards
        target - id value of the taarget card

    ret:
        0 if duplicate is found
        1 if duplicate is not found
    */

    uint count = 0;
    struct Card *dummy = head;
    while(dummy != NULL) {

        if(dummy->id == target)
            count++;

        dummy = dummy->next;
    }

    if(count > 1)
        return 0;

    return 1;
}

uint validate_cards(struct Card *head) {
    /*
    Validates the singly linked lists of cards

    args:
        head - the head of the singly linked lists of cards

    ret:
        if all cards are valid returns '1'
        else returns '0'
    */
    
    uint ret = 1;
    printf("\nValidating Cards...\n");

    struct Card *dummy = head;
    int cards_count = 0;
    
    while(dummy->next != NULL) {

        dummy = dummy->next;

        uint is_valid_card = 1;
        cards_count++;

        if(find_duplicacy(head, dummy->id) == 0) {
            printf("Card ID: %d is duplicate\n", dummy->id);
            ret = 0;
            continue;
        }
        
        for(int i = 0; i < 2; ++i) {
            
            uint write = dummy->state[i].write == 0 || dummy->state[i].write == 1;
            uint move = dummy->state[i].move == 'L' || dummy->state[i].move == 'R' || dummy->state[i].move == 'S';
            struct Card *find = search_card(head, dummy->state[i].next_card);
            
            if(!write || !move || (!find && dummy->state[i].next_card != 0)) {
                is_valid_card = 0;
                break;
            }
        }

        if(is_valid_card) {
            printf("Card ID: %d is valid\n", dummy->id);
        
        } else {
            printf("Card ID: %d is not valid\n", dummy->id);
            ret = 0;
        }
    }

    printf("\n");

    if(cards_count < 1) {
        printf("Invalid: No cards availabl\n");
        return 0;
    }
    return ret;
}

void print_cards(struct Card *head) {
    /*
    Prints all the cards in the singly linked lists

    args:
        head - pointer to the head of the card
    */

    printf("Printing cards...\n-----------------\n");

    struct Card *dummy = head->next;
    while(dummy != NULL) {

        printf("\nCard - %d\n", dummy->id);
        printf("S  W M N\n");
        printf("0  %d %c %d\n", dummy->state[0].write, dummy->state[0].move, dummy->state[0].next_card);
        printf("1  %d %c %d\n\n", dummy->state[1].write, dummy->state[1].move, dummy->state[1].next_card);
        
        dummy = dummy->next;
    }
    printf("-----------------\n");
}
