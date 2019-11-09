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
    wug_destroy(g);
}

int main()
{
    empty_mst_test();
}
