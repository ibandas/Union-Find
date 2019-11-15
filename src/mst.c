#include "mst.h"
#include "union_find.h"
#include "libipd.h"
#include "stdlib.h"

// Citation: https://jeffpar.github.io/kbarchive/kb/073/Q73853/
// Citation: https://stackoverflow.com/questions/23051964/how-to-qsort-an-array-of-struct
int compare_weights(const void *a, const void *b)
{
    const struct wu_edge *elem1 = a;
    const struct wu_edge *elem2 = b;
    if (elem1->w < elem2->w) {
        return -1;
    }
    else if (elem1->w > elem2->w) {
        return 1;
    }
    else {
        return 0;
    }
}

wu_graph_t kruskal_mst(wu_graph_t g)
{
    struct wu_edge out[wug_edge_count(g)];
    size_t used = wug_get_edges(g, out, wug_edge_count(g));

    qsort(out, wug_edge_count(g), sizeof(struct wu_edge), compare_weights);

    union_find_t uf = NULL;
    wu_graph_t mst = NULL;


    if (!(uf = uf_create(wug_size(g))))
        goto finish;

    if (!(mst = wug_create(wug_size(g))))
        goto finish;

    // One edge just returns the current tree since it is a MST
    if (used == 1) {
        return g;
    }
    size_t index = 0;
    while (index < used) {
        object_t u = uf_find(uf, out[index].u);
        object_t v = uf_find(uf, out[index].v);
        if (u != v) {
//            printf("%lu", out[index].u);
//            printf("\n");
//            printf("%lu", out[index].v);
//            printf("\n");
//            printf("%lf", out[index].w);
//            printf("\n");
//            printf("\n");
            wug_set_edge(mst, out[index].u, out[index].v, out[index].w);
            uf_union(uf, u, v);
        }
        index++;
    }
    // If you always return via this label then you'll always
    // clean up properly:
    finish:
    uf_destroy(uf);
    wug_destroy(g);
    return mst;
}

