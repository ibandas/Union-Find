#include "union_find.h"
#include "stdlib.h"

#include <stdint.h>

// You can use an 8-bit integer (a/k/a a byte, a/k/a an unsigned char)
// to hold ranks because they won’t ever get too big. (Why?)
typedef uint8_t rank_t;

// Represents a union-find having `size_` objects.
//
// C Invariants:
//  - `id_`   points to an initialized array of `size_` `object_t`s.
//  - `rank_` points to an initialized array of `size_` `rank_t`s.
//  - every element of the `id_` array is a valid index for the
//    `id_` array (i.e., it’s less than `size_`).
//
// Definitions:
//  - A *path* is a sequence of distinct indices i[0], i[1], ...,
//    i[k-1] such that id_[i[0]] == i[1] && id_[i[1]] == i[2] && ... &&
//    id_[i[k-2]] == i[k-1].
//  - The length of the path is `k`, the number of indices in the
//    sequence.
//  - A cycle is a path with id_[i[k-1]] = i[0].
//
// Union-find Invariants:
//  - There are no non-trivial cycles in the `id_` array; that is,
//    every cycle has length 1. (Those are the roots.)
//  - The ranks of the roots are upper bounds on the heights of
//    their trees; that is, for each index `r` such that id_[r] == r
//    there is no sequence of indices ending in `r` whose length
//    exceeds `rank_[r]`.
//
// (The values of `rank_[r]` for non-roots don’t matter.)
//
struct union_find
{
    object_t*  id_;
    rank_t*    rank_;
    size_t     size_;
};

union_find_t uf_create(size_t n)
{
    union_find_t res  = malloc(sizeof(struct union_find) +
                                       n * sizeof(object_t) +
                                       n * sizeof(rank_t));
    if (!res) return NULL;
    res->size_ = n;
    return res;
}

void uf_destroy(union_find_t uf)
{
    free(uf);
}

// TODO: Why create a uf and destroy previous one instead of just changing current uf?
bool uf_union(union_find_t uf, object_t m, object_t n)
{
    if (uf_same_set(uf, m, n)){
        return false;
    }
    else {
        if(uf->rank_[m] > uf->rank_[n]){
            uf->id_[m] = uf_find(uf, n);
        }
        else {
            uf->id_[n] = uf_find(uf, m);
        }
        return true;
    }
}

object_t uf_find(union_find_t uf, object_t m)
{
    if (uf->id_[m] == m){
        return m;
    }
    else {
        uf_find(uf, uf->id_[m]);
    }
}

bool uf_same_set(union_find_t uf, object_t m, object_t n)
{
    // Nothing to do.
    return uf_find(uf, m) == uf_find(uf, n);
}

size_t uf_size(union_find_t uf)
{
    // All good here.
    return uf->size_;
}

