//
// Created by joped on 03/10/2020.
//

#ifndef MAIN_C_STACKS_H
#define MAIN_C_STACKS_H
typedef struct _Stack Stack;

Stack* create_element(int);
Stack* push_FIFO(Stack*,Stack*);
int remove_FIFO(Stack**);
Stack* pull_FIFO(Stack**);
Stack* erase_FIFO(Stack*);
void print_FIFO(Stack*);

Stack** create_LIFO(Stack*);
Stack** push_LIFO(Stack**,Stack*);
int remove_LIFO(Stack**);
Stack* pull_LIFO(Stack**);
Stack** erase_LIFO(Stack**);
void print_LIFO(Stack**);

#endif //MAIN_C_STACKS_H
