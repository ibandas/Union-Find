#include "mst.h"
#include "libipd.h"
#include <assert.h>

// This test should pass already; you definitely need many more.
static void empty_mst_test()
{
    wu_graph_t g = wug_create(5);
    assert(g);

    wu_graph_t mst = kruskal_mst(g);
    assert(mst);

    CHECK_INT(wug_edge_count(mst), 0);

    wug_destroy(mst);
}
// Prints the minimum spanning tree
static void view_mst_test(size_t mst_edges, struct wu_edge out_mst[])
{
    size_t index = 0;
    while (index < mst_edges) {
        printf("%lu", out_mst[index].u);
        printf("\n");
        printf("%lu", out_mst[index].v);
        printf("\n");
        printf("%lf", out_mst[index].w);
        printf("\n");
        printf("\n");
        index++;
    }
}


// Used in example_graph_01
static weight_t const WEIGHT1 = 5.5;
static weight_t const WEIGHT2 = 3.3;

static wu_graph_t example_graph_01(size_t n)
{
    assert(n > 2);

    wu_graph_t g = wug_create(n);

    for (vertex_t u = 1; u < n - 1; ++u) {
        wug_set_edge(g, 0, u,     WEIGHT1);
        wug_set_edge(g, u, n - 1, WEIGHT2);
    }

    return g;
}

static void mst_test_01()
{
    size_t n = 5;
    wu_graph_t g = example_graph_01(n);
    wu_graph_t mst = kruskal_mst(g);
    CHECK_INT(wug_edge_count(mst), 4);
    wug_destroy(mst);
}

// Ten Vertices + Fourteen Edges
static wu_graph_t example_graph_02()
{
    wu_graph_t g = wug_create(10);

    wug_set_edge(g, 1, 2, 1);
    wug_set_edge(g, 1, 3, 5);
    wug_set_edge(g, 2, 4, 3);
    wug_set_edge(g, 4, 5, 4);
    wug_set_edge(g, 4, 6, 7);
    wug_set_edge(g, 5, 6, 3);
    wug_set_edge(g, 6, 3, 4);
    wug_set_edge(g, 6, 7, 6);
    wug_set_edge(g, 6, 8, 2);
    wug_set_edge(g, 8, 7, 6);
    wug_set_edge(g, 7, 0, 1);
    wug_set_edge(g, 7, 3, 7);
    wug_set_edge(g, 7, 9, 5);
    wug_set_edge(g, 9, 1, 2);

    return g;
}

static void mst_test_02()
{
    wu_graph_t g = example_graph_02();
    wu_graph_t mst = kruskal_mst(g);
    CHECK_INT(wug_edge_count(mst), 9);
    struct wu_edge out_mst[wug_edge_count(mst)];
    size_t mst_used = wug_get_edges(mst, out_mst, wug_edge_count(mst));
    //First Edge
    CHECK_UINT(out_mst[0].u, 0);
    CHECK_UINT(out_mst[0].v, 7);
    CHECK_DOUBLE(out_mst[0].w, 1);

    //Second Edge
    CHECK_UINT(out_mst[1].u, 1);
    CHECK_UINT(out_mst[1].v, 2);
    CHECK_DOUBLE(out_mst[1].w, 1);

    //Third Edge
    CHECK_UINT(out_mst[2].u, 1);
    CHECK_UINT(out_mst[2].v, 9);
    CHECK_DOUBLE(out_mst[2].w, 2);

    //Fourth Edge
    CHECK_UINT(out_mst[3].u, 2);
    CHECK_UINT(out_mst[3].v, 4);
    CHECK_DOUBLE(out_mst[3].w, 3);

    //Fifth Edge
    CHECK_UINT(out_mst[4].u, 3);
    CHECK_UINT(out_mst[4].v, 6);
    CHECK_DOUBLE(out_mst[4].w, 4);

    //Sixth Edge
    CHECK_UINT(out_mst[5].u, 4);
    CHECK_UINT(out_mst[5].v, 5);
    CHECK_DOUBLE(out_mst[5].w, 4);

    //Seventh Edge
    CHECK_UINT(out_mst[6].u, 5);
    CHECK_UINT(out_mst[6].v, 6);
    CHECK_DOUBLE(out_mst[6].w, 3);

    //Eighth Edge
    CHECK_UINT(out_mst[7].u, 6);
    CHECK_UINT(out_mst[7].v, 8);
    CHECK_DOUBLE(out_mst[7].w, 2);

    //Ninth Edge
    CHECK_UINT(out_mst[8].u, 7);
    CHECK_UINT(out_mst[8].v, 9);
    CHECK_DOUBLE(out_mst[8].w, 5);

    view_mst_test(mst_used, out_mst);
    wug_destroy(mst);
}

// Three Vertices + Three Edges
static wu_graph_t example_graph_03()
{
    wu_graph_t g = wug_create(3);

    wug_set_edge(g, 0, 1, 1);
    wug_set_edge(g, 0, 2, 8);
    wug_set_edge(g, 1, 2, 5);

    return g;
}

static void mst_test_03() {
    wu_graph_t g = example_graph_03();
    wu_graph_t mst = kruskal_mst(g);
    CHECK_INT(wug_edge_count(mst), 2);
    struct wu_edge out_mst[wug_edge_count(mst)];
    size_t mst_used = wug_get_edges(mst, out_mst, wug_edge_count(mst));
    //First Edge
    CHECK_UINT(out_mst[0].u, 0);
    CHECK_UINT(out_mst[0].v, 1);
    CHECK_DOUBLE(out_mst[0].w, 1);

    //Second Edge
    CHECK_UINT(out_mst[1].u, 1);
    CHECK_UINT(out_mst[1].v, 2);
    CHECK_DOUBLE(out_mst[1].w, 5);

    wug_destroy(mst);
}

// Two vertices + One Edge
static wu_graph_t example_graph_04()
{
    wu_graph_t g = wug_create(2);

    wug_set_edge(g, 0, 1, 1.5);

    return g;
}

static void mst_test_04() {
    wu_graph_t g = example_graph_04();
    wu_graph_t mst = kruskal_mst(g);
    CHECK_INT(wug_edge_count(mst), 1);
    struct wu_edge out_mst[wug_edge_count(mst)];
    size_t mst_used = wug_get_edges(mst, out_mst, wug_edge_count(mst));

    //First Edge
    CHECK_UINT(out_mst[0].u, 0);
    CHECK_UINT(out_mst[0].v, 1);
    CHECK_DOUBLE(out_mst[0].w, 1.5);

    wug_destroy(mst);
}

// One Vertex + No Edge
static wu_graph_t example_graph_05()
{
    wu_graph_t g = wug_create(1);

    return g;
}

static void mst_test_05() {
    wu_graph_t g = example_graph_05();
    wu_graph_t mst = kruskal_mst(g);
    CHECK_INT(wug_edge_count(mst), 0);

    wug_destroy(mst);
}

int main()
{
    empty_mst_test();
    mst_test_01();
    mst_test_02();
    mst_test_03();
    mst_test_04();
    mst_test_05();
}
