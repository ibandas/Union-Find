#pragma once

#include <math.h>
#include <stdbool.h>
#include <stddef.h>

// Vertices are natural numbers:
typedef size_t vertex_t;

// Weights are doubles:
typedef double weight_t;

// Absent edges are represented by positive infinity:
#define NO_EDGE ((double)INFINITY)

// A weighted, undirected graph is represented as a pointer to
// an abstract implementation type (defined in the .c file):
typedef struct wu_graph* wu_graph_t;

// Represents a single weighted, undirected edge. (These are returned
// by `wug_get_edges`.)
struct wu_edge {
    vertex_t u, v;
    weight_t w;
};


// Creates a new graph with the given number of vertices and no edges.
// Ownership: the caller must free the new graph using `wug_destroy`.
// Errors: Returns NULL on out-of-memory.
wu_graph_t wug_create(size_t n);

// Frees the resources associated with a graph.
// Ownership: Caller gives up ownership of the graph and must not use it
// again.
void wug_destroy(wu_graph_t);

// Returns the number of vertices in the graph.
size_t wug_size(wu_graph_t);

// Sets the weight of the edge between two vertices. This can be used to
// add an edge, or by passing NO_EDGE, to remove one.
void wug_set_edge(wu_graph_t, vertex_t, vertex_t, weight_t);

// Gets the weight of the edge between two vertices. Returns `NO_EDGE` if
// there is no such edge.
weight_t wug_get_edge(wu_graph_t, vertex_t, vertex_t);

// Gets the weight of the edge between two vertices. Returns `NO_EDGE` if
// there is no such edge.
bool wug_has_edge(wu_graph_t, vertex_t, vertex_t);

// Returns the degree (number of neighbors) of vertex `v`.
size_t wug_neighbor_count(wu_graph_t, vertex_t v);

// Stores all the neighbors of vertex `v` (up to `out_size`) in `out`
// and returns the number of vertices stored.
size_t wug_get_neighbors(wu_graph_t, vertex_t v, vertex_t out[], size_t out_size);

// Returns the total count of edges in the graph; does not include duplicates
// like (3, 4) and (4, 3), since for an undirected graph those are the same edge.
size_t wug_edge_count(wu_graph_t);

// Stores all the edges (up to `out_size`) in `out` and returns the
// number of edges stored.  Does not include duplicates like (3, 4)
// and (4, 3), since for an undirected graph those are the same edge.
size_t wug_get_edges(wu_graph_t, struct wu_edge out[], size_t out_size);

