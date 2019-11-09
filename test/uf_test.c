#include "union_find.h"
#include "libipd.h"
#include <assert.h>

static void create_size_and_destroy(size_t n)
{
    union_find_t uf = uf_create(n);
    assert(uf);
    
    CHECK_UINT( uf_size(uf), n );

    uf_destroy(uf);
}

int main()
{
    create_size_and_destroy(0);
    create_size_and_destroy(5);
    create_size_and_destroy(5000);
}
