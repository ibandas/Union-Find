cmake_minimum_required(VERSION 3.3)
project(hw06 C CXX)
include(.ipd/cmake/CMakeLists.txt)

add_c_test(graph_test
        test/graph_test.c
        src/wu_graph.c)

add_c_test(uf_test
        test/uf_test.c
        src/union_find.c)

add_c_test(mst_test
        test/mst_test.c
        src/mst.c
        src/wu_graph.c
        src/union_find.c)
