#include <stdio.h>

#include "lib/Graph_module/ISPs.h"
#include "lib/Graph_module/graph.h"

int main(int argc,char const *argv[]) {
    FILE *fp_preview = NULL,*fp =NULL;
    List** ISP_graph=NULL;
    List* teste;
    int max_node_value=1;

    fp_preview=open_ISP(fp_preview);
    fp=open_ISP(fp);

    ISP_graph=read_ISP(fp_preview,fp,&max_node_value);

    close_ISP(fp_preview);  //fecha o ficheiro apos ser analisado
    close_ISP(fp);  //fecha o ficheiro apos ser analisado

    free_ISP(ISP_graph,max_node_value);

    return 0;
}
