#include <stdlib.h>

#include "ch11_search.h"
#include "ch06_queue.h"

static void bfs_colour_all(Graph* graph, BfsNode* bfs) {
    // iterate over the vertex and colour them
    BfsNode* temp;
    for (Node* nd = graph->vertices.head; nd; nd = nd->next) {
        temp = vertex_data(nd->data); // extract bfs node 
        if (graph->compare(temp, bfs)) {
            bfs_set_colour(temp, gray);
            bfs_set_hops(temp, 0);
        } else { 
            bfs_set_colour(temp, white);
            bfs_set_hops(temp, -1);
        }
    }
}

int bfs(Graph* graph, BfsNode* bfs, List* list) { 
    bfs_colour_all(graph, bfs);
    // set up a queue
    Queue queue;
    queue_init(&queue, NULL);
    // find the vertex with given BfsNode
    Vertex* vx;
    if (graph_vertex(graph, bfs, &vx) == 0)
        return -1;
    if (queue_enqueue(&queue, vx) != 0) {
        queue_clear(&queue);
        return -1;
    }
    // helper variable
    BfsNode* temp;
    // visit vertices bread-first
    while (queue_size(&queue) > 0) {
        vx = queue_peek(&queue);
        for (Node* nd = vx->adjacent.head; nd; nd = nd->next) {
            if (bfs_get_colour(nd->data) != white)
                continue;
            bfs_set_colour(nd->data, gray); // visited
            bfs_set_hops(nd->data, bfs_get_hops(nd->data) + 1);
            // fetch vertex and enqueue it
            if (graph_vertex(graph, nd->data, &vx) != 0)
                return -1;
            if (queue_enqueue(&queue, vx) != 0) {
                queue_clear(&queue);
                return -1;
            }
        }
        if (queue_dequeue(&queue, (void**)&vx) != 0) {
            queue_clear(&queue);
            return -1;
        }
        bfs_set_colour(vertex_data(vx), black); // processed
    }
    list_init(list, NULL);
    for (Node* nd = graph->vertices.head; nd; nd = nd->next) {
        temp = vertex_data(nd->data);
        if (bfs_get_hops(temp) == -1) 
            continue;
        if (list_insert(list, list->tail, temp) != 0) {
            list_clear(list);
            return -1;
        }
    }
    return 0; 
}

static void dfs_colour_all(Graph* graph) {
    // iterate over the vertex and colour them
    DfsNode* temp;
    for (Node* nd = graph->vertices.head; nd; nd = nd->next) {
        temp = vertex_data(nd->data);
        dfs_set_colour(temp, white);
    }
}

static int dfs_core(Graph* graph, Vertex* vertex, List* ordered) {
    DfsNode* dfs = vertex_data(vertex); 
    dfs_set_colour(dfs, gray);
    Vertex* vx;
    for (Node* nd = vertex->adjacent.head; nd; nd = nd->next) {
        if (graph_vertex(graph, nd->data, &vx) != 0)
            return -1;
        if (dfs_get_colour(vertex_data(vx)) != white)
            continue;
        if (dfs_core(graph, vx, ordered) != 0)
            return -1;
    }
    dfs_set_colour(dfs, black);
    if (list_insert(ordered, ordered->tail, vertex) != 0)
        return -1;
    return 0;
}

int dfs(Graph* graph, List* ordered) {
    dfs_colour_all(graph);
    for (Node* nd = graph->vertices.head; nd; nd = nd->next) {
        if (dfs_get_colour(vertex_data(nd->data)) != white)
            continue;
        if (dfs_core(graph, nd->data, ordered) != 0)
            return -1;
    }
    return 0;
}

