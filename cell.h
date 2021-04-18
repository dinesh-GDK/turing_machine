#include<stdio.h>
#include<stdlib.h>

struct Cell {
    uint val;
    struct Cell *next;
    struct Cell *prev;
};

void print_tape(struct Cell *head) {

    struct Cell *dummy = head;

    while(dummy->prev != NULL)
        dummy = dummy->prev;

    while(dummy != NULL) {
        printf("%d ", dummy->val);
        dummy = dummy->next;
    }

    printf("\n\n");
}

struct Cell *move(struct Cell *head, char dir) {

    if(dir == 'R') {

        if(head->next == NULL) {
            struct Cell *temp = (struct Cell*)malloc(sizeof(struct Cell));
            temp->val = 0;
            head->next = temp;
            temp->prev = head;
            temp->next = NULL;
        }

        head = head->next;
    
    } else if(dir == 'L') {
            if(head->prev == NULL) {
            struct Cell *temp = (struct Cell *)malloc(sizeof(struct Cell));
            temp->val = 0;
            head->prev = temp;
            temp->next = head;
            temp->prev = NULL;
        }

        head = head->prev;

    } else if(dir == 'S') {

    } else {
        printf("Invalid Direction\n");
        exit(0);
    }

    return head;
}

void get_initial_tape(struct Cell *head, char *file) {

    FILE *fptr = fopen(file, "r");
    if(fptr == NULL) {
        printf("Error reading file\n");
        exit(0);
    }

    struct Cell *dummy = head;
    char temp;

    while(fscanf(fptr, "%c", &temp) != EOF) {
        dummy->val = temp - '0';
        dummy = move(dummy, 'R');
        fscanf(fptr, "%c", &temp);
    }

    dummy = move(dummy, 'L');
    free(dummy->next);
    dummy->next = NULL;
}

uint validate_tape(struct Cell *head) {

    struct Cell* dummy = head;

    while(dummy != NULL) {
        
        if(dummy->val != 0 && dummy->val != 1) {
            printf("Invalid Tape!\n");
            return 0;
        }

        dummy = dummy->next;
    }

    printf("Valid tape\n\n");
    return 1;
}

uint tape_count_ones(struct Cell *cell) {
    
    uint count = 0;
    
    struct Cell *dummy = cell;
    while(dummy != NULL) {
        if(dummy->val == 1)
            count++;
        dummy = dummy->prev;
    }

    dummy = cell->next;
    while(dummy != NULL) {
        if(dummy->val == 1)
            count++;
        dummy = dummy->next;
    }

    return count;
}
