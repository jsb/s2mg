#include "gtest/gtest.h"

#include <s2mg/map/map_dimensions.hpp>
#include <s2mg/map/handles.hpp>

TEST(halfedge_handle, face_circulation) {
    s2mg::map_dimensions dims{5, 4};
    for (std::size_t he_index = 0; he_index < dims.n_halfedges(); ++he_index) {
        s2mg::halfedge_handle heh{dims, he_index};
        for (int i = 0; i < 3; ++i) {
            heh = heh.next();
        }
        EXPECT_EQ(he_index, heh.index());
    }
}

TEST(halfedge_handle, vertex_circulation) {
    s2mg::map_dimensions dims{5, 4};
    for (std::size_t he_index = 0; he_index < dims.n_halfedges(); ++he_index) {
        s2mg::halfedge_handle heh{dims, he_index};
        for (int i = 0; i < 6; ++i) {
            heh = heh.opp();
            heh = heh.next();
        }
        EXPECT_EQ(he_index, heh.index());
    }
}
