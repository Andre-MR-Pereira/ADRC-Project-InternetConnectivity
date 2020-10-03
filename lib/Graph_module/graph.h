#ifndef _GRAPH_H
#define _GRAPH_H

typedef struct Node List;

struct Node {
    int vertices;
    char edges;
    List *next;
};

List** create_graph(int max_node_value);
List** fill_ISP(List** ISP_graph,int tail,int head,char mode);
List* initNode(void);
void free_ISP(List** ISP_graph,int max_node_value);
List* insertHeadList(List* next,List* item);
void free_node_list(List** ISP_graph,int max_node_value);
void print_graph(List** ISP_graph,int max_node_value);
void remove_node(List** ISP_graph,int ISP_vertice,int node_vertice);
List* find_node(List** ISP_graph,int ISP_vertice,int node_vertice);

#endif