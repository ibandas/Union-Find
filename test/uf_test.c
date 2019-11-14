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

static void test_uf_find(void)
{
    union_find_t uf = uf_create(10);
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

static void test_uf_union_part1(void) {
    union_find_t uf = uf_create(10);
    uf_union(uf, 0, 9);
    CHECK_UINT(get_uf_id_index(uf, 0), 9);
    uf_union(uf, 0, 8);
    CHECK_UINT(get_uf_id_index(uf, 8), 9);
    uf_union(uf, 7, 9);
    CHECK_UINT(get_uf_id_index(uf, 7), 9);
    uf_union(uf, 1, 2);
    CHECK_UINT(get_uf_id_index(uf, 1), 2);
    uf_union(uf, 3, 4);
    CHECK_UINT(get_uf_id_index(uf, 3), 4);
    uf_union(uf, 5, 6);
    CHECK_UINT(get_uf_id_index(uf, 5), 6);
    uf_union(uf, 5, 7);
    CHECK_UINT(get_uf_id_index(uf, 5), 6);
    CHECK_UINT(get_uf_id_index(uf, 6), 9);
    uf_union(uf, 1, 3);
    CHECK_UINT(get_uf_id_index(uf, 1), 2);
    CHECK_UINT(get_uf_id_index(uf, 2), 4);
    uf_union(uf, 1, 5);
    CHECK_UINT(get_uf_id_index(uf, 1), 4);
    CHECK_UINT(get_uf_id_index(uf, 5), 9);
    get_all_uf_test(uf);
    uf_destroy(uf);
}

// Code Walk Tests
static void test_union_0_1(void)
{
    union_find_t uf = uf_create(3);
    uf_union(uf, 0, 1);
    object_t r0 = uf_find(uf, 0);
    object_t r1 = uf_find(uf, 1);
    CHECK_UINT( r0, r1 );

    uf_union(uf, 2, 0);
    CHECK_UINT( uf_find(uf, 2), r0 );
}

int main()
{
    create_size_and_destroy(0);
    create_size_and_destroy(5);
    create_size_and_destroy(10);
    create_size_and_destroy(100);
    create_size_and_destroy(5000);
    test_uf_find();
    test_union_0_1();
    test_uf_union_part1();
}
