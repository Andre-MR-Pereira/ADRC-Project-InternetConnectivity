#ifndef _GRAPH_H
#define _GRAPH_H

typedef struct Node List;

struct Node {
    int vertices;
    char edges;
    List *next;
};

List** create_graph(int max_node_value);
List** fill_ISP(List** ISP_graph,int tail,int head,int mode);
List* initNode(void);
List* insertHeadList(List* next,List* item);
void print_graph(List** ISP_graph,int max_node_value);

#endif