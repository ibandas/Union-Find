#include "mst.h"
#include "union_find.h"

wu_graph_t kruskal_mst(wu_graph_t g)
{
    union_find_t uf = NULL;
    wu_graph_t mst = NULL;

    if (!(uf = uf_create(wug_size(g))))
        goto finish;

    if (!(mst = wug_create(wug_size(g))))
        goto finish;



    // If you always return via this label then you'll always
    // clean up properly:
    finish:
    uf_destroy(uf);
    return mst;
}
