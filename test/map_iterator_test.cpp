#include "gtest/gtest.h"

#include <s2mg/map/map_dimensions.hpp>
#include <s2mg/map/handles.hpp>

class map_iterator_test : public ::testing::Test
{
protected:
    s2mg::map_dimensions map{5, 4};
};

TEST_F(map_iterator_test, halfedge_opp_opp) {
    EXPECT_EQ(static_cast<std::ptrdiff_t>(map.n_vertices()),  std::distance(map.vertices().begin(),  map.vertices().end()));
    EXPECT_EQ(static_cast<std::ptrdiff_t>(map.n_faces()),     std::distance(map.faces().begin(),     map.faces().end()));
    EXPECT_EQ(static_cast<std::ptrdiff_t>(map.n_halfedges()), std::distance(map.halfedges().begin(), map.halfedges().end()));
    EXPECT_EQ(static_cast<std::ptrdiff_t>(map.n_edges()),     std::distance(map.edges().begin(),     map.edges().end()));
}