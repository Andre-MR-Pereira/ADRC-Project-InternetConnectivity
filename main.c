#include <stdio.h>
#include <stdlib.h>

#include "lib/Graph_module/ISPs.h"
#include "lib/Graph_module/graph.h"
#include "lib/Graph_module/Search.h"
#include "lib/Graph_module/SearchCommercial.h"

int main(int argc,char const *argv[]) {
    FILE *fp_preview = NULL,*fp =NULL;
    List** ISP_graph=NULL;
    int max_node_value=1;
    int *parent = NULL;

    fp_preview=open_ISP(fp_preview);
    fp=open_ISP(fp);

    ISP_graph=read_ISP(fp_preview,fp,&max_node_value);

    close_ISP(fp_preview);  //fecha o ficheiro apos ser analisado
    close_ISP(fp);  //fecha o ficheiro apos ser analisado

    parent = DFS_C(ISP_graph, max_node_value, 1);
    for (int i = 0; i < max_node_value; ++i)
        printf("%d vem de %d\n", i+1, parent[i]);

    free(parent);
    free_ISP(ISP_graph,max_node_value);

    return 0;
}
