//
// Created by joped on 03/10/2020.
#include <stdlib.h>
#include <stdio.h>

#include "Stacks.h"

struct _Stack {
    int node;
    struct _Stack* next;
};

int get_node(Stack* a){
    return a->node;
}

Stack* create_element(int node) {
    Stack *ele = (Stack *) malloc(sizeof(Stack));
    ele->node = node;
    ele->next = NULL;
    return ele;
}

Stack* push_LIFO(Stack* LIFO,Stack* new){
    new->next=LIFO;
    LIFO = new;
    return LIFO;
}

int remove_LIFO(Stack** LIFO){
    if(*LIFO == NULL) return 0;
    else{
        int node= (*LIFO)->node;
        Stack* aux = *LIFO;
        *LIFO = (*LIFO)->next;
        free(aux);
        return node;
    }
}

Stack* pull_LIFO(Stack** LIFO){
    Stack* node= (*LIFO);
    if(*LIFO == NULL) return *LIFO;
    else{
        *LIFO = (*LIFO)->next;
        return node;
    }
}

Stack* erase_LIFO(Stack* LIFO){
    Stack *aux = NULL;
    while(LIFO != NULL){
        aux=LIFO;
        LIFO=LIFO->next;
        free(aux);
    }
    return LIFO;
}

void print_LIFO(Stack* LIFO){
    while(LIFO != NULL) {
        printf("%i ", LIFO->node);
        LIFO = LIFO->next;
    }
    printf("\n");
}


Stack** create_FIFO(Stack* new){
    Stack** FIFO=(Stack **) malloc(sizeof(Stack*)*2);
    FIFO[0] = new;
    FIFO[1] = new;
    return FIFO;
}

Stack** push_FIFO(Stack** FIFO,Stack* new){
    FIFO[1]->next=new;
    FIFO[1] = new;
    return FIFO;
}

int remove_FIFO(Stack** FIFO){
    int node = remove_LIFO(&FIFO[0]);
    if(FIFO[0] == NULL) FIFO[1] = NULL;
    return node;
}

Stack* pull_FIFO(Stack** FIFO){
    return pull_LIFO(&FIFO[0]);
}

Stack** erase_FIFO(Stack** FIFO){
    FIFO[0]= erase_LIFO(FIFO[0]);
    free(FIFO);
    return NULL;
}

void print_FIFO(Stack** FIFO){
    if (FIFO==NULL) return;
    print_LIFO(FIFO[0]);
}

//

