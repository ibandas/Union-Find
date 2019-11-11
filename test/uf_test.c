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

static void test_uf_find(size_t n, object_t m)
{

    union_find_t uf = uf_create(n);
    uf_find(uf, m);

}

int main()
{
    create_size_and_destroy(0);
    create_size_and_destroy(5);
    create_size_and_destroy(10);
    create_size_and_destroy(100);
    create_size_and_destroy(5000);
}
