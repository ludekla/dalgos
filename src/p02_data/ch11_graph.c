#include <stdlib.h> // NULL
#include <string.h> // memset

#include "ch11_graph.h"

void graph_init(Graph* graph, match_f compare, purge_f purge) {
    graph->vcount = 0;
    graph->ecount = 0;
    list_init(&graph->vertices, NULL);
    graph->compare = compare;
    graph->purge = purge;
}

void graph_clear(Graph* graph) {
    Vertex* vertex;
    // iterate over the vertices
    while (list_size(&graph->vertices) > 0) {
        if (list_remove(&graph->vertices, NULL, (void**)&vertex) == 0) {
            // handle adjacency set
            set_clear(&vertex->adjacent);
            if (graph->purge != NULL)
                graph->purge(vertex->data);
            free(vertex);
        }
    }
    list_clear(&graph->vertices);
    memset(graph, 0, sizeof(Graph));
}

int graph_insert_vertex(Graph* graph, const void* data) {
    Vertex* vx;
    if (graph_vertex(graph, data, &vx) == 1)
        return -1; // vertex already present
    if ((vx = (Vertex*)malloc(sizeof(Vertex))) == NULL)
        return -1;
    vx->data = (void*)data;
    set_init(&vx->adjacent, graph->compare, NULL);
    if (list_insert(&graph->vertices, graph->vertices.tail, (void*)vx) != 0)
        return -1;
    graph->vcount++;
    return 0; 
}

int graph_insert_edge(Graph* graph, const void* data1, const void* data2) {
    Vertex* vx;
    if (graph_vertex(graph, data1, &vx) == 0)
        return -1; // vertex not found
    if (set_insert(&vx->adjacent, data2) != 0)
        return -1; // some error or adjacency already present
    graph->ecount++;
    return 0;
}

int graph_remove_vertex(Graph* graph, void** data) {
    Node* nd;
    Node* prev = NULL;
    for (nd = graph->vertices.head; nd; nd = nd->next) {
        if (set_is_member(vertex_adjacent(nd->data), *data))
            // still adjacency of a vertex
            return -1;
        if (!graph->compare(vertex_data(nd->data), *data))
            prev = nd;
    }
    if (nd == NULL)
        return -1; // not found
    if (set_size(vertex_adjacent(nd->data)) > 0)
        return -1; // vertex to be purged must have no adjacencies
    if (list_remove(&graph->vertices, prev, data) != 0)
        return -1;
    *data = vertex_data(nd->data);
    free(nd->data);
    graph->vcount--;
    return 0;
}

int graph_remove_edge(Graph* graph, void* data1, void** data2) {
    Vertex* vx;
    if (graph_vertex(graph, data1, &vx) == 0)
        return -1; // vertex not found
    // vertex has been found
    if (set_remove(&vx->adjacent, data2) != 0)
        return -1;
    graph->ecount--;
    return 0;
}

int graph_vertex(Graph* graph, const void* data, Vertex** vertex) {
    Node* nd;
    // look for the vertex
    for (nd = (graph->vertices).head; nd; nd = nd->next) {
        if (graph->compare(vertex_data(nd->data), data))
            break;
    }
    if (nd == NULL)
        return 0; // not found
    *vertex = (Vertex*)nd->data;
    return 1; // found
}

int graph_is_adjacent(Graph* graph, const void* data1, const void* data2) {
    Node* nd;
    // look for the vertex with data1
    for (nd = (graph->vertices).head; nd; nd = nd->next) {
        if (graph->compare(vertex_data(nd->data), data1))
            break;
    }
    if (nd == NULL)
        return 0; // first vertex not even found
    return set_is_member(vertex_adjacent(nd->data), data2);
}
