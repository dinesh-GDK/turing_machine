#include <stdio.h>
#include <stdlib.h>

struct Cell {
    uint val;
    struct Cell *next;
    struct Cell *prev;
};

void print_tape(struct Cell *head) {
    /*
    Prints the tape (doubly linked list containing all cells)

    args:
        head - head of the tape (doubly linked list containing all cells)
    */

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
    /*
    Moves the head of the tape (doubly linked list containing all cells)

    args:
        head - head of the tape (doubly linked list containing all cells)
        dir - direction to move
            L - move left
            R - move right
            S - stay
            if excluded options are given the program will exit
            (the validate_cards function will take care of this)

    ret:
        returns the head of the pointer moved to the specified direction

    If when the shifted cell is non-exixting it creates a new cell and initialises
    its valus to '0' and adds to the tape (doubly linked list containing all cells)
    */

    if(dir == 'R') {

        if(head->next == NULL) {
            struct Cell *temp = (struct Cell*)malloc(sizeof(struct Cell));
            if(temp == NULL) {
                printf("System out of memory");
                exit(0);
            }
            temp->val = 0;
            head->next = temp;
            temp->prev = head;
            temp->next = NULL;
        }

        head = head->next;
    
    } else if(dir == 'L') {
        
        if(head->prev == NULL) {
            struct Cell *temp = (struct Cell *)malloc(sizeof(struct Cell));
            if(temp == NULL) {
                printf("System out of memory");
                exit(0);
            }
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
    /*
    Creates the initial tape (doubly linked list) from the file with the 
    specified format 

    args:
        head - the one cell created at the beginning
        file - the file with the specified format to create tape
    */

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
    /*
    Validates the tape (the value of each cell must be '0'/'1')

    args:
        head - head of the tape (doubly linked list containing all cells)
    */

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

uint tape_count_ones(struct Cell *head) {
    /*
    Counts the number of ones in the tape (doubly linked list containing all cells)

    args:
        head - head of the tape (doubly linked list containing all cells)

    ret:
        count - number of ones in the tape
    */
    
    uint count = 0;
    
    struct Cell *dummy = head;
    while(dummy != NULL) {
        if(dummy->val == 1)
            count++;
        dummy = dummy->prev;
    }

    dummy = head->next;
    while(dummy != NULL) {
        if(dummy->val == 1)
            count++;
        dummy = dummy->next;
    }

    return count;
}

void free_tape(struct Cell *head) {
    /*
    Frees the memory of cells

    args:
        head - pointer to the head of the cell
    */

   struct Cell *temp1 = head, *temp2;
   while(temp1 != NULL) {
        temp2 = temp1->next;
        free(temp1);
        temp1 = temp2;
   }
}
