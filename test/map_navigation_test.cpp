#include "gtest/gtest.h"

#include <s2mg/map_data/map_dimensions.hpp>
#include <s2mg/map_data/handles.hpp>

class map_navigation_test : public ::testing::Test
{
protected:
    s2mg::map_dimensions dims{5, 4};
};

TEST_F(map_navigation_test, halfedge_opp_opp) {
    for (std::size_t he_index = 0; he_index < dims.n_halfedges(); ++he_index) {
        s2mg::halfedge_handle heh{dims, he_index};
        EXPECT_EQ(heh, heh.opp().opp());
    }
}

TEST_F(map_navigation_test, halfedge_next_prev) {
    for (std::size_t he_index = 0; he_index < dims.n_halfedges(); ++he_index) {
        s2mg::halfedge_handle heh{dims, he_index};
        EXPECT_EQ(heh, heh.next().prev());
    }
}

TEST_F(map_navigation_test, halfedge_face_circulation) {
    for (std::size_t he_index = 0; he_index < dims.n_halfedges(); ++he_index) {
        s2mg::halfedge_handle heh{dims, he_index};
        for (int i = 0; i < 3; ++i) {
            heh = heh.next();
        }
        EXPECT_EQ(he_index, heh.index());
    }
}

TEST_F(map_navigation_test, halfedge_vertex_circulation) {
    for (std::size_t he_index = 0; he_index < dims.n_halfedges(); ++he_index) {
        s2mg::halfedge_handle heh{dims, he_index};
        for (int i = 0; i < 6; ++i) {
            heh = heh.opp();
            heh = heh.next();
        }
        EXPECT_EQ(he_index, heh.index());
    }
}

TEST_F(map_navigation_test, halfedge_to_edge) {
    for (std::size_t he_index = 0; he_index < dims.n_halfedges(); ++he_index) {
        s2mg::halfedge_handle heh{dims, he_index};
        auto eh0 = heh.eh();
        auto eh1 = heh.opp().eh();
        EXPECT_EQ(eh0, eh1);
    }
}

TEST_F(map_navigation_test, edge_to_halfedge) {
    for (std::size_t e_index = 0; e_index < dims.n_edges(); ++e_index) {
        s2mg::edge_handle eh{dims, e_index};
        auto heh0 = eh.heh(0);
        auto heh1 = eh.heh(1);
        EXPECT_EQ(heh0.opp(), heh1);
    }
}

TEST_F(map_navigation_test, edge_opposite_vertices) {
    for (std::size_t e_index = 0; e_index < dims.n_edges(); ++e_index) {
        s2mg::edge_handle eh{dims, e_index};
        auto heh0 = eh.heh(0);
        auto heh1 = eh.heh(1);
        EXPECT_EQ(heh0.from_vh(), heh1.to_vh());
        EXPECT_EQ(heh0.to_vh(), heh1.from_vh());
    }
}

TEST_F(map_navigation_test, face_to_halfedge_to_face) {
    for (std::size_t f_index = 0; f_index < dims.n_faces(); ++f_index) {
        s2mg::face_handle fh0{dims, f_index};
        auto fh1 = fh0.heh().next().fh();
        auto fh2 = fh0.heh().next().next().fh();
        EXPECT_EQ(fh0, fh1);
        EXPECT_EQ(fh0, fh2);
    }
}

TEST_F(map_navigation_test, vertex_to_halfedge) {
    for (std::size_t v_index = 0; v_index < dims.n_vertices(); ++v_index) {
        s2mg::vertex_handle vh{dims, v_index};
        EXPECT_EQ(vh, vh.heh().from_vh());
    }
}

