#ifndef GRAPH_H
#define GRAPH_H

#include "ch07_set.h"

typedef struct {
    void* data;
    Set adjacent;
} Vertex;

#define vertex_data(vertex) (((Vertex*)(vertex))->data)

#define vertex_adjacent(vertex) (&((Vertex*)(vertex))->adjacent)

typedef struct {
    int vcount;
    int ecount;
    List vertices;
    match_f compare;
    purge_f purge;
} Graph;

void graph_init(Graph* graph, match_f compare, purge_f purge);

void graph_clear(Graph* graph);

int graph_insert_vertex(Graph* graph, const void* data);

int graph_insert_edge(Graph* graph, const void* data1, const void* data2);

int graph_remove_vertex(Graph* graph, void** data);

int graph_remove_edge(Graph* graph, void* data1, void** data2);

int graph_vertex(Graph* graph, const void* data, Vertex** vertex);

int graph_is_adjacent(Graph* graph, const void* data1, const void* data2);

#define graph_vertices(graph) ((graph)->vertices)

#define graph_ecount(graph) ((graph)->ecount)

#define graph_vcount(graph) ((graph)->vcount)

#endif
