#define _FORK_H

typedef struct Node List;

struct Node {
    int index;
    int column;
    int line;
    int weight;
    List *next;
};

typedef struct fork {
    int vertices;
    int edges;
    List **list_adj;
} Fork;