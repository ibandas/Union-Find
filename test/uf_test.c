#include "union_find.h"
#include "libipd.h"
#include <assert.h>
#include <stdlib.h>

static union_find_t union_find_create_checked(size_t n)
{
    union_find_t res = uf_create(n);
    if (res) return res;

    perror("uf_create_checked");
    exit(1);
}

#define uf_create union_find_create_checked

static void create_size_and_destroy(size_t n)
{
    union_find_t uf = uf_create(n);
    assert(uf);

    CHECK_UINT( uf_size(uf), n );

    uf_destroy(uf);
}

static void test_uf_find(size_t n)
{
    union_find_t uf = uf_create(n);
    set_uf_id_(uf);
    CHECK_UINT(uf_find(uf, 1), 1);
    CHECK_UINT(uf_find(uf, 3), 3);
    set_uf_id_index(uf, 3, 2);
    CHECK_UINT(uf_find(uf, 3), 2);
    set_uf_id_index(uf, 9, 0);
    CHECK_UINT(uf_find(uf, 9), 0);
    set_uf_id_index(uf, 9, 5);
    CHECK_UINT(uf_find(uf, 9), 5);
    set_uf_id_index(uf, 5, 3);
    CHECK_UINT(uf_find(uf, 9), 2);
    CHECK_UINT(uf_find(uf, 5), 2);

    uf_destroy(uf);
}

int main()
{
    create_size_and_destroy(0);
    create_size_and_destroy(5);
    create_size_and_destroy(10);
    create_size_and_destroy(100);
    create_size_and_destroy(5000);
    test_uf_find(10);
}
