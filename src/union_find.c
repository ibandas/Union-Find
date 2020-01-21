#include "union_find.h"
#include "stdlib.h"
#include "libipd.h"
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

union_find_t uf_create(size_t n) {
    union_find_t res = malloc(sizeof *res);
    if (!res) goto bail1;

    res->id_ = malloc(n * sizeof(object_t));
    if (!res->id_) goto bail2;

    res->rank_ = malloc(n * sizeof(rank_t));
    if (!res->id_) goto bail3;


    res->size_ = n;
    size_t index = 0;
    while(index < res->size_) {
        res->id_[index] = index;
        res->rank_[index] = 0;
        index++;
    }
    return res;

    bail3:
    free(res->id_);
    bail2:
    free(res);
    bail1:
    return NULL;
}
void uf_destroy(union_find_t uf)
{
    if (!uf) {
        return;
    }
    free(uf->id_);
    free(uf->rank_);
    free(uf);
}

//Citation: https://algorithms.tutorialhorizon.com/disjoint-set-union-find-algorithm-union-by-rank-and-path-compression/
bool uf_union(union_find_t uf, object_t m, object_t n)
{
    object_t m_root = uf_find(uf, m);
    object_t n_root = uf_find(uf, n);
    if (m_root == n_root) {
        return false;
    }
    if(uf->rank_[m_root] < uf->rank_[n_root]){
        uf->id_[m_root] = n_root;
    }
    else if (uf->rank_[m_root] > uf->rank_[n_root]) {
        uf->id_[n_root] = m_root;
    }
    else {
        uf->id_[m_root] = n_root;
        uf->rank_[n_root] = uf->rank_[n_root] + 1;
    }
    return true;
}

object_t uf_find(union_find_t uf, object_t m)
{
    if (uf->id_[m] == m){
        return m;
    }
    else {
        object_t r = uf_find(uf, uf->id_[m]);
        uf->id_[m] = r;
        return r;
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

void set_uf_id_index(union_find_t uf, size_t index, size_t value) {
    uf->id_[index] = value;
}

object_t get_uf_id_index(union_find_t uf, size_t index) {
    return uf->id_[index];
}

object_t get_all_uf_test(union_find_t uf) {
    size_t index = 0;
    while(index < uf->size_) {
        printf("%lu ", uf->id_[index]);
        index++;
    }
}
