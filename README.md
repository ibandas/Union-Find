# IPD Homework 6: Union-Find

## Summary

In this assignment you will implement a rank-balanced, path-compressing
union-find, and then you will use it to implement Kruskal’s MST
algorithm.

## Goals

The goals of this assignment are to gain familiarity with union-find and
with graph algorithms, and to practice using and implementing ADTs in C.

## Specification

There are two parts to this assignment, union-find and MST.

### Part I: Union-Find

File [`src/union_find.h`] contains an interface to the Union-Find ADT as
a set of C type and function declarations, including `union_find_t`
defined as a pointer to an *incomplete type*, `struct union_find`. File
[`src/union_find.c`] contains the definition of the `union_find` struct
and stub definitions of the functions declared in its header.

Your job is to complete the implementation of the union-find operations
in [`src/union_find.c`]. Use the final version of union-find that we saw
in class: lazy union with path compression, and union-by-rank to keep
trees balanced. Note that:

  - Union-by-weight won't work because we are storing ranks as 8-bit
    unsigned integers to save space. Ranks cannot overflow that size
    integer but weights easily can. (Why?)
    
  - The `uf_create` function needs to perform *three* heap allocations,
    any of which can fail. The `uf_create` function is specified to
    return `NULL` when it can’t allocate, which means the client program
    might keep going. Thus, if one or two allocations succeed and then
    an allocation fails, it’s important not to leak the successful
    allocations.

Of course, you need to write tests to ensure that your implementation is
correct. Write them in [`test/uf_test.c`]. We’ve given you much less
helpful code for setting up your tests this week, so if you want to test
effectively you should think about what helper functions you might
design to do so. You may want to look at [`test/graph_test.c`] for
inspiration.

### Part II: Minimum Spanning Tree

For this part, you will use (but not modify) the graph API in
[`src/wu_graph.h`] and [`src/wu_graph.c`].  File [`src/mst.h`] contains
a declaration of a minimum-spanning tree function `kruskal_mst`, which
takes a `wu_graph_t` (a weighted, undirected graph) and returns a new
`wu_graph_t` containing only its minimum spanning tree/forest. In
[`src/mst.c`] there’s a stub implementation of `kruskal_mst` that
creates a new graph `mst` with the correct number of vertices but no
edges and returns it. Complete the `kruskal_mst` function to add the
correct edges to `mst` before returning it.

Note that like `uf_create`, `kruskal_mst` should avoid leaking memory,
even if errors occur.

And don’t forget to test it. Do we really need to tell you?

## Deliverables

For this homework you must:

  - Implement the `uf_create`, `uf_destroy`, `uf_union`, and `uf_find`
    functions in [`src/union_find.c`].

  - Implement the `kruskal_mst` function in [`src/mst.c`].

  - Add plenty more test cases to [`test/uf_test.c`] and
    [`test/mst_test.c`].

  - Adhere to the [IPD Style Manual for C and C++][style].
  

[`src/wu_graph.h`]:    src/wu_graph.h
[`src/wu_graph.c`]:    src/wu_graph.c
[`test/graph_test.c`]: test/graph_test.c
[`src/union_find.h`]:  src/union_find.h
[`src/union_find.c`]:  src/union_find.c
[`test/uf_test.c`]:    test/uf_test.c
[`src/mst.h`]:         src/mst.h
[`src/mst.c`]:         src/mst.c
[`test/mst_test.c`]:   test/mst_test.c

[style]: https://github.com/nu-ipd/notes/blob/master/style2.md

