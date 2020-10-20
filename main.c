#include <stdio.h>
#include <stdlib.h>

#include "lib/Graph_module/ISPs.h"
#include "menus.h"


int main(int argc,char const *argv[]) {
    FILE *fp_preview = NULL,*fp =NULL;
    List** ISP_graph=NULL;
    int max_node_value=1,count_f=0,true_size=1;
    int *parent = NULL,*top_f=NULL,*list_top=NULL;
    fp_preview=open_ISP(fp_preview);
    fp=open_ISP(fp);

    ISP_graph=read_ISP(fp_preview,fp,&max_node_value,&top_f,&list_top,&count_f,&true_size);

    close_ISP(fp_preview);  //fecha o ficheiro apos ser analisado
    close_ISP(fp);  //fecha o ficheiro apos ser analisado

    showInitMenu(ISP_graph,top_f,max_node_value,list_top,count_f,true_size);

    free(parent);
    free(top_f);
    free(list_top);
    free_ISP(ISP_graph,max_node_value);

    return 0;
}
