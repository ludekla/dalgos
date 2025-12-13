#ifndef SEARCH_H
#define SEARCH_H

#include "ch11_graph.h"

typedef enum {
    white,  // unvisited
    gray,   // seen
    black   // processed (adjacencies acknowledged)
} VertexColour;

// Bread-first Search
typedef struct {
    void* data;
    VertexColour colour;
    int n_hops;
} BfsNode;

// Depth-first Search
typedef struct {
    void* data;
    VertexColour colour;
} DfsNode;

static void bfs_colour(Graph* graph, BfsNode* bfs); 

int bfs(Graph* graph, BfsNode* bfs, List* list);

static void dfs_colour(Graph* graph); 

static int dfs_core(Graph* graph, Vertex* vx, List* ordered);

int dfs(Graph* graph, List* ordered);

#define bfs_get_colour(vertex) (((BfsNode*)(vertex))->colour)

#define bfs_set_colour(vertex, value) \
    (((BfsNode*)(vertex))->colour = (value))

#define bfs_get_hops(vertex) (((BfsNode*)(vertex))->n_hops)

#define bfs_set_hops(vertex, value) \
    (((BfsNode*)(vertex))->n_hops = (value))

#define dfs_get_colour(vertex) (((DfsNode*)(vertex))->colour)

#define dfs_set_colour(vertex, value) \
    (((DfsNode*)(vertex))->colour = (value))

#endif
