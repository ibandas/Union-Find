#include "wu_graph.h"

#include <stdlib.h>

// Stores a weighted, undirected graph as the lower triangle of
// its adjacency matrix. That is, the matrix contains edge weights
// in this order: (0, 0), (1, 0), (1, 1), (2, 0), (2, 1), (2, 2), ...
struct wu_graph
{
    size_t   size_;
    weight_t matrix_[0];
};

// Finds the matrix capacity for a graph with `n` vertices; equivalently,
// this returns the index of the `n`th row of the triangle.
static size_t capacity_(size_t n)
{
    return n * (n + 1) / 2;
}

// Finds the index of the edge between `u` and `v`.
static size_t index_(vertex_t u, vertex_t v)
{
    if (v > u)
        return capacity_(v) + u;
    else
        return capacity_(u) + v;
}

// Returns a pointer to the weight of the edge between vertices
// `u` and `v`.
static weight_t* edge_(wu_graph_t g, vertex_t u, vertex_t v)
{
    return &g->matrix_[index_(u, v)];
}

wu_graph_t wug_create(size_t n)
{
    size_t capacity = capacity_(n);
    wu_graph_t res  = malloc(sizeof(struct wu_graph) +
                                     capacity * sizeof(weight_t));
    if (!res) return NULL;

    res->size_ = n;

    for (size_t i = 0; i < capacity; ++i)
        res->matrix_[i] = NO_EDGE;

    return res;
}

void wug_destroy(wu_graph_t g)
{
    free(g);
}

size_t wug_size(wu_graph_t g)
{
    return g->size_;
}

void wug_set_edge(wu_graph_t g, vertex_t u, vertex_t v, weight_t w)
{
    *edge_(g, u, v) = w;
}

weight_t wug_get_edge(wu_graph_t g, vertex_t u, vertex_t v)
{
    return *edge_(g, u, v);
}

bool wug_has_edge(wu_graph_t g, vertex_t u, vertex_t v)
{
    return wug_get_edge(g, u, v) != NO_EDGE;
}

size_t wug_neighbor_count(wu_graph_t g, vertex_t v)
{
    size_t count = 0;

    for (vertex_t u = 0; u < g->size_; ++u)
        if (wug_has_edge(g, u, v))
            ++count;

    return count;
}

size_t wug_get_neighbors(wu_graph_t g, vertex_t v, vertex_t out[], size_t out_size)
{
    size_t count = 0;

    for (vertex_t u = 0; u < g->size_ && count < out_size; ++u)
        if (wug_has_edge(g, u, v))
            out[count++] = u;

    return count;
}

size_t wug_edge_count(wu_graph_t g)
{
    size_t count = 0;
    size_t limit = capacity_(wug_size(g));

    for (size_t i = 0; i < limit; ++i)
        if (g->matrix_[i] != NO_EDGE)
            ++count;

    return count;
}

size_t wug_get_edges(wu_graph_t g, struct wu_edge out[], size_t out_size)
{
    size_t fill = 0;

    for (vertex_t u = 0; u < g->size_ && fill < out_size; ++u) {
        for (vertex_t v = u; v < g->size_ && fill < out_size; ++v) {
            weight_t w = wug_get_edge(g, u, v);
            if (w != NO_EDGE) {
                out[fill].u = u;
                out[fill].v = v;
                out[fill].w = w;
                ++fill;
            }
        }
    }

    return fill;
}

