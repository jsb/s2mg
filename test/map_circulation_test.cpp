#include "gtest/gtest.h"

#include <s2mg/map_data/map_dimensions.hpp>
#include <s2mg/map_data/handles.hpp>
#include <s2mg/map_data/map_data.hpp>

class map_circulation_test : public ::testing::Test
{
protected:
    s2mg::map_dimensions map{5, 4};
};

TEST_F(map_circulation_test, expected_vertex_range_sizes) {
    for (auto vh : map.vertices()) {
        EXPECT_EQ(6, std::distance(vh.adjacent_vertices().begin(),  vh.adjacent_vertices().end()));
        EXPECT_EQ(6, std::distance(vh.incident_faces().begin(),     vh.incident_faces().end()));
        EXPECT_EQ(6, std::distance(vh.incident_halfedges().begin(), vh.incident_halfedges().end()));
        EXPECT_EQ(6, std::distance(vh.incident_edges().begin(),     vh.incident_edges().end()));
    }
}

TEST_F(map_circulation_test, expected_face_range_sizes) {
    for (auto fh : map.faces()) {
        EXPECT_EQ(3, std::distance(fh.incident_vertices().begin(),  fh.incident_vertices().end()));
        EXPECT_EQ(3, std::distance(fh.adjacent_faces().begin(),     fh.adjacent_faces().end()));
        EXPECT_EQ(3, std::distance(fh.incident_halfedges().begin(), fh.incident_halfedges().end()));
        EXPECT_EQ(3, std::distance(fh.incident_edges().begin(),     fh.incident_edges().end()));
    }
}

TEST_F(map_circulation_test, expected_visits) {
    s2mg::vertex_data<int> visit_count{map};
    for (auto vh : map.vertices()) {
        for (auto adjacent_vh : vh.adjacent_vertices()) {
            ++visit_count[adjacent_vh];
        }
    }
    for (auto vh : map.vertices()) {
        ASSERT_EQ(6, visit_count[vh]);
    }
}
