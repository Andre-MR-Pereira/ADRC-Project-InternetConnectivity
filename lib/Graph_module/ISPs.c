#include "ISPs.h"
#include "graph.h"

void read_ISP(FILE *fp_preview,FILE *fp){
    int max_node_value=1,tail,head,mode;
    List** ISP_graph;

    while(fscanf(fp_preview,"%d %d %d",&tail,&head,&mode)!=EOF){
        if(tail>max_node_value){
            max_node_value=tail;
        }
    }

    ISP_graph=create_graph(max_node_value);

    while(fscanf(fp,"%d %d %d",&tail,&head,&mode)!=EOF){
        ISP_graph=fill_ISP(ISP_graph,tail,head,mode);
    }
    print_graph(ISP_graph,max_node_value);
    return;
}