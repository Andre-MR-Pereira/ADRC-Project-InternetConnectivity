#include <stdio.h>
#include <stdlib.h>

#include "lib/Graph_module/ISPs.h"
#include "menus.h"

int main(int argc,char const *argv[]) {
    FILE *fp_preview = NULL,*fp =NULL;  //inititalizacao de variaveis para tratamento do ficheiro
    List** ISP_graph=NULL;  //initializacao do grafo que vai ser analizado
    int max_node_value=1,count_f=0,true_size=1; //initializacao de variaveis de tratamento de grafo
    int *parent = NULL,*top_f=NULL,*list_top=NULL;
    //abertura do ficheiro em analise
  
    fp_preview=open_ISP(fp_preview,argc,argv);
    fp=open_ISP(fp,argc,argv);

    //leitura e preenchimento do grafo da rede em analise
    ISP_graph=read_ISP(fp_preview,fp,&max_node_value,&top_f,&list_top,&count_f,&true_size);

    //fechar o ficheiro em análise
    close_ISP(fp_preview);  //fecha o ficheiro apos ser analisado
    close_ISP(fp);  //fecha o ficheiro apos ser analisado

    //abertura dos menus para processamento das escolhas do utilizador
    showInitMenu(ISP_graph,top_f,max_node_value,list_top,count_f,true_size);

    //libertação da memória alocada para o tratamento do problema
    free(parent);
    free(top_f);
    free(list_top);
    free_ISP(ISP_graph,max_node_value);

    return 0;
}
