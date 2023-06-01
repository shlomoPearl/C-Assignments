# include <stdio.h>
#include "edge.c"

typedef struct _Node{
        int id;
        int inWeight;
        int keyPrevNode;
        Edge *edge_in;
        Edge *edge_out;
    }Node;