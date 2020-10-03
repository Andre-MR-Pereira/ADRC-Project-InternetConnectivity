#include "ISPs.h"

#include <stdlib.h>

List** read_ISP(FILE *fp_preview,FILE *fp,int *max_node_value){
    int tail,head;
    char mode;
    List** ISP_graph;

    while(fscanf(fp_preview,"%d %d %c",&tail,&head,&mode)!=EOF){
        if(tail>*max_node_value){
            *max_node_value=tail;
        }
    }

    ISP_graph=create_graph(*max_node_value);

    while(fscanf(fp,"%d %d %c",&tail,&head,&mode)!=EOF){
        ISP_graph=fill_ISP(ISP_graph,tail,head,mode);
    }

    print_graph(ISP_graph,*max_node_value);

    return ISP_graph;
}

FILE* open_ISP(FILE* file_pointer){

    file_pointer=fopen("../lib/Assets/pdf_example.txt","r");
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