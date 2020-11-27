#include "ISPs.h"

#include <stdlib.h>


//funcao para ler o ficheiro e criar o grafo para ser analisado
List** read_ISP(FILE *fp_preview,FILE *fp,int *max_node_value,int **top_f,int **list_top,int*count_f,int* true_size){
    //inicializacao de variaveis
    int tail,head,u=0;
    char mode;
    List** ISP_graph;

    //procura do maior no da rede
    while(fscanf(fp_preview,"%d %d %c",&tail,&head,&mode)!=EOF){
        if(tail>*max_node_value){
            *max_node_value=tail;   //guarda o maior valor do no encontrado
        }
    }

    *true_size=*max_node_value; //guarda o maior valor do no encontrado
    *top_f = (int*)malloc((*max_node_value)*sizeof(int));
    //inicializa todos os valores a 1
    for(int i =0; i<*max_node_value;i++) (*top_f)[i]=1;

    ISP_graph=create_graph(*max_node_value);//cria o grafo para ser preenchido
    *count_f = *max_node_value;

    while(fscanf(fp,"%d %d %c",&tail,&head,&mode)!=EOF){    //le agora o ficheiro mais uma vez, mas com a intencao de preencher o grafo
        ISP_graph=fill_ISP(ISP_graph,tail,head,mode);   //adiciona um novo no ao grafo
        if(mode=='3'&&(*top_f)[tail-1]==1){
            (*top_f)[tail-1]=0;
            (*count_f)--;
        }
    }

    *list_top = (int*)malloc(sizeof(int)*(*max_node_value));
    (*list_top)[0]=0;
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

FILE* open_ISP(FILE* file_pointer,int argc,char const *argv[]){ //abre o ficheiro da rede

    file_pointer=fopen("../lib/Assets/pdf_example.txt","r");
    if (file_pointer == NULL) {
        return (FILE *) EXIT_FAILURE;
    }
    /*if (argc != 2) {
        exit(0);
    }

    file_pointer = fopen(argv[1], "r"); //abrir o ficheiro a ser analisado
    if (file_pointer == NULL) {
        exit(0);
    }*/

    return file_pointer;
}

void close_ISP(FILE *file_pointer){ //fecha o ficheiro
    fclose(file_pointer);
}