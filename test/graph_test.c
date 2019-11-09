#include "wu_graph.h"
#include "libipd.h"

#include <assert.h>
#include <stdlib.h>

// Returns the lesser of two arguments. (Evaluates the expression
// that produces the result twice.)
#define MIN(A, B)   ((A) < (B)? (A) : (B))

// Avoids UB by always checking for NULL after calling `wug_create`.
// We don't want the real `wug_create` to bail out like this because
// the client code might prefer dealing with OOM some other way, but
// for testing it's better to just exit.
static wu_graph_t wug_create_checked(size_t n)
{
    wu_graph_t res = wug_create(n);
    if (res) return res;

    perror("wug_create_checked");
    exit(1);
}

// We tell the C preprocessor to replace `wug_create` with
// `wug_create_checked` for the rest of this file. We need to
// do this AFTER defining `wug_create_checked` or it would break
// the definition of `wug_create_checked`. (How?)
#define wug_create wug_create_checked


// Used in generated graphs and tests thereof.
static weight_t const WEIGHT1 = 3.3;
static weight_t const WEIGHT2 = 5.5;

// Creates graph where 0 and n-1 connect to all the other
// vertices but not to each other. That means that 0 and n-1
// will both have degree n-2 and all other vertices will have
// degree 2.
//
// PRECONDITION: n > 2
static wu_graph_t example_graph(size_t n)
{
    assert(n > 2);

    wu_graph_t g = wug_create(n);

    for (vertex_t u = 1; u < n - 1; ++u) {
        wug_set_edge(g, 0, u,     WEIGHT1);
        wug_set_edge(g, u, n - 1, WEIGHT2);
    }

    return g;
}


// Tests `wug_size` on an empty graph of size `n`.
static void test_empty_size(size_t n)
{
    wu_graph_t g = wug_create(n);
    CHECK_UINT(wug_size(g), n);
    wug_destroy(g);
}


// Builds a graph of size `n` containing a single cycle
// 0, 1, ..., n-1, 0 and then checks every potential edge.
static void test_graph_ring(size_t n)
{
    wu_graph_t g = wug_create(n);

    for (vertex_t u = 0; u < n; ++u) {
        vertex_t v = (u + 1) % n;
        wug_set_edge(g, u, v, u * v);
    }

    for (vertex_t u = 0; u < n; ++u)
        for (vertex_t v = 0; v < n; ++v)
            if ((u + 1) % n == v || (v + 1) % n == u)
                CHECK_DOUBLE( wug_get_edge(g, u, v), u * v );
            else
                CHECK_DOUBLE( wug_get_edge(g, u, v), NO_EDGE );

    wug_destroy(g);
}


// Builds an `example_graph` of size `n` and checks that
// `wug_neighbor_count` produces the correct answer for every vertex.
static void test_neighbor_count(size_t n) {
    wu_graph_t g = example_graph(n);

    for (size_t u = 0; u < n; ++u) {
        if (u == 0 || u == n - 1)
            CHECK_UINT( wug_neighbor_count(g, u), n - 2 );
        else
            CHECK_UINT( wug_neighbor_count(g, u), 2 );
    }

    wug_destroy(g);
}


static void test_get_neighbors_capacity(wu_graph_t g,
                                        vertex_t v,
                                        size_t cap,
                                        size_t count)
{
    vertex_t buf[cap];
    size_t n = wug_size(g);

    size_t used = wug_get_neighbors(g, v, buf, cap);
    CHECK_UINT(used, MIN(count, cap));

    if (v == 0 || v == n - 1) {
        for (size_t i = 0; i < used; ++i)
            CHECK_UINT(buf[i], i + 1);
    } else {
        if (0 < used) CHECK_UINT(buf[0], 0);
        if (1 < used) CHECK_UINT(buf[1], n - 1);
    }
}


static void test_get_neighbors(size_t n)
{
    wu_graph_t g = example_graph(n);

    for (size_t u = 0; u < n; ++u) {
        size_t degree = wug_neighbor_count(g, u);
        test_get_neighbors_capacity(g, u, MIN(degree, 2) - 2, degree);
        test_get_neighbors_capacity(g, u, degree,             degree);
        test_get_neighbors_capacity(g, u, degree + 2,         degree);
    }

    wug_destroy(g);
}


static void test_get_edges_capacity(wu_graph_t g, size_t cap, size_t count)
{
    struct wu_edge buf[cap];
    size_t n = wug_size(g);

    size_t used = wug_get_edges(g, buf, cap);
    CHECK_UINT(used, MIN(count, cap));

    for (size_t i = 0, v = 1; v < n - 1 && i < used; ++i, ++v) {
        CHECK_UINT(buf[i].u, 0);
        CHECK_UINT(buf[i].v, v);
        CHECK_DOUBLE(buf[i].w, WEIGHT1);
    }

    for (size_t i = n - 2, v = 1; v < n - 1 && i < used; ++i, ++v) {
        CHECK_UINT(buf[i].u, v);
        CHECK_UINT(buf[i].v, n - 1);
        CHECK_DOUBLE(buf[i].w, WEIGHT2);
    }
}


static void test_get_edges(size_t n)
{
    wu_graph_t g = example_graph(n);
    size_t n_edges = 2 * (n - 2);

    test_get_edges_capacity(g, MIN(n_edges, 2) - 2, n_edges);
    test_get_edges_capacity(g, n_edges,             n_edges);
    test_get_edges_capacity(g, n_edges + 2,         n_edges);

    wug_destroy(g);
}


static void test_edge_count(size_t n)
{
    wu_graph_t g = example_graph(n);
    CHECK_UINT( wug_edge_count(g), 2 * (n - 2));
    wug_destroy(g);
}


int main()
{
    test_empty_size(0);
    test_empty_size(5);

    test_graph_ring(5);
    test_graph_ring(8);

    test_neighbor_count(5);
    test_neighbor_count(12);

    test_get_neighbors(5);
    test_get_neighbors(12);

    test_edge_count(5);
    test_edge_count(12);

    test_get_edges(5);
    test_get_edges(12);
}
