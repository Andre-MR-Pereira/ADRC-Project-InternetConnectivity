#include "ISPs.h"

#include <stdlib.h>



List** read_ISP(FILE *fp_preview,FILE *fp,int *max_node_value,int **top_f,int **list_top,int*count_f,int* true_size){
    int tail,head,u=0;
    char mode;
    List** ISP_graph;

    while(fscanf(fp_preview,"%d %d %c",&tail,&head,&mode)!=EOF){
        if(tail>*max_node_value){
            *max_node_value=tail;
        }
    }
    *true_size=*max_node_value;
    *top_f = (int*)malloc((*max_node_value)*sizeof(int));
    for(int i =0; i<*max_node_value;i++) (*top_f)[i]=1;
    ISP_graph=create_graph(*max_node_value);
    *count_f = *max_node_value;

    while(fscanf(fp,"%d %d %c",&tail,&head,&mode)!=EOF){
        ISP_graph=fill_ISP(ISP_graph,tail,head,mode);
        if(mode=='3'&&(*top_f)[tail-1]==1){
            (*top_f)[tail-1]=0;
            (*count_f)--;
        }
    }

    *list_top = (int*)malloc(sizeof(int)*(*max_node_value));
    for(int i =0; i<*max_node_value;i++) {
        if (ISP_graph[i]==NULL) {
            (*top_f)[i]=0;
            (*count_f)--;
            (*true_size)--;
        }
        else if ((*top_f)[i]==1) (*list_top)[u++]=i+1;
    }

     //print_graph(ISP_graph,*max_node_value);

    return ISP_graph;
}

FILE* open_ISP(FILE* file_pointer){

    file_pointer=fopen("../lib/Assets/ex.txt","r");
    if (file_pointer == NULL) {
        return (FILE *) EXIT_FAILURE;
    }

    /*fp = fopen(argv[1], "r"); //abrir o ficheiro a ser analisado
    if (fp == NULL || argc != 2) {
        return (FILE *) EXIT_FAILURE;
    }*/

    return file_pointer;
}

void close_ISP(FILE *file_pointer){
    fclose(file_pointer);
}