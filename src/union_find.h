#pragma once

#include <stdbool.h>
#include <stddef.h>

// We will represent objects (in sets) using type `size_t`.
typedef size_t object_t;

// A union-find is represented as a pointer to an incomplete type.
typedef struct union_find* union_find_t;


// Creates a new union-find of `n` objects.
//
// Ownership: The result is owned by the caller, who must free it with
// `uf_destroy`.
//
// Errors: Returns NULL for out-of-memory.
union_find_t uf_create(size_t n);

// Frees the resources associated with a union-find. The argument is
// allowed to be NULL, in which case this function does nothing.
//
// Ownership: Caller gives up ownership of the union-find and must not
// use it again.
void uf_destroy(union_find_t);

// Unions the sets containing the two given objects into one set if they
// aren't one set already. Returns `true` if a change was made or `false`
// if the objects were already in the same set.
bool uf_union(union_find_t, object_t, object_t);

// Finds the representative object for the set containing the given object.
object_t uf_find(union_find_t, object_t);

// Determines whether two objects belong to the same set.
bool uf_same_set(union_find_t, object_t, object_t);

// Returns the number of objects in the union-find (a/k/a one more
// than the largest valid object).
size_t uf_size(union_find_t);

