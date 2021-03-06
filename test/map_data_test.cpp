#include "gtest/gtest.h"

#include <s2mg/map_data/map_dimensions.hpp>
#include <s2mg/map_data/handles.hpp>
#include <s2mg/map_data/map_data.hpp>

class map_data_test : public ::testing::Test
{
protected:
    s2mg::map_dimensions map{5, 4};
};

TEST_F(map_data_test, expected_sizes) {
    s2mg::vertex_data<int>   vi{map};
    s2mg::face_data<int>     fi{map};
    s2mg::halfedge_data<int> hi{map};
    s2mg::edge_data<int>     ei{map};
    EXPECT_EQ(map.n_vertices(),  vi.size());
    EXPECT_EQ(map.n_faces(),     fi.size());
    EXPECT_EQ(map.n_halfedges(), hi.size());
    EXPECT_EQ(map.n_edges(),     ei.size());
}

TEST_F(map_data_test, simple_arithmetic) {
    s2mg::face_data<int> fi{map};
    {
        s2mg::vertex_data<int> vi{map};
        for (auto vh : map.vertices()) {
            vi[vh] = 3;
        }
        for (auto fh : map.faces()) {
            fi[fh] = 0;
            for (auto fvh : fh.incident_vertices()) {
                fi[fh] += vi[fvh];
            }
        }
    }
    for (auto fh : map.faces()) {
        ASSERT_EQ(9, fi[fh]);
    }
}
