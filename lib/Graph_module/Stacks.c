//
// Created by joped on 03/10/2020.
#include <stdlib.h>
#include <stdio.h>

#include "Stacks.h"

struct _Stack {
    int node;
    struct _Stack* next;
};

Stack* create_element(int node) {
    Stack *ele = (Stack *) malloc(sizeof(Stack));
    ele->node = node;
    ele->next = NULL;
    return ele;
}

Stack* push_FIFO(Stack* FIFO,Stack* new){
    new->next=FIFO;
    FIFO = new;
    return FIFO;
}

int remove_FIFO(Stack** FIFO){
    int node= (*FIFO)->node;
    Stack* aux = *FIFO;
    if(*FIFO == NULL) return 0;
    else{
        *FIFO = (*FIFO)->next;
        free(aux);
        return node;
    }
}

Stack* pull_FIFO(Stack** FIFO){
    Stack* node= (*FIFO);
    if(*FIFO == NULL) return *FIFO;
    else{
        *FIFO = (*FIFO)->next;
        return node;
    }
}

Stack* erase_FIFO(Stack* FIFO){
    Stack *aux = NULL;
    while(FIFO != NULL){
        aux=FIFO;
        FIFO=FIFO->next;
        free(aux);
    }
    return FIFO;
}

void print_FIFO(Stack* FIFO){
    while(FIFO != NULL) {
        printf("%i ", FIFO->node);
        FIFO = FIFO->next;
    }
    printf("\n");
}
Stack** create_LIFO(Stack* new){

    Stack** LIFO=(Stack **) malloc(sizeof(Stack*)*2);
    LIFO[0] = new;
    LIFO[1] = new;
    return LIFO;
}
Stack** push_LIFO(Stack** LIFO,Stack* new){
    LIFO[1]->next=new;
    LIFO[1] = new;
    return LIFO;
}
/*
int remove_LIFO(Stack** LIFO){
    int node= LIFO[0]->node;
    Stack* aux = LIFO[0];
    if(LIFO[0] == NULL) return LIFO[0];
    else{
        LIFO[0] = LIFO[0]->next;
        free(aux);
        return node;
    }
}
*/
int remove_LIFO(Stack** LIFO){
    return remove_FIFO(&LIFO[0]);
}

Stack* pull_LIFO(Stack** LIFO){
    return pull_FIFO(&LIFO[0]);
}

Stack** erase_LIFO(Stack** LIFO){
    LIFO[0]= erase_FIFO(LIFO[0]);
    free(LIFO);
    return NULL;
}

void print_LIFO(Stack** LIFO){
    if (LIFO==NULL) return;
    print_FIFO(LIFO[0]);
}



//

