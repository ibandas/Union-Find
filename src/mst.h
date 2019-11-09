#pragma once

#include "wu_graph.h"

// Computes a minimum spanning forest by Kruskal's algorithm.
//
// Ownership: The result is heap-allocated and must be freed by
// the caller using `wug_destroy`.
//
// Errors: Returns NULL on out-of-memory.
wu_graph_t kruskal_mst(wu_graph_t);

