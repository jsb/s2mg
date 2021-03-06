#include "halfedge_handle.hpp"
#include "face_handle.hpp"
#include "vertex_handle.hpp"
#include "edge_handle.hpp"

#include <cassert>

namespace s2mg {

face_handle halfedge_handle::fh() const
{
    return {map(), index() / 3};
}

vertex_handle halfedge_handle::to_vh() const
{
    auto aux = *this;
    while ((aux.index() % 6) != 2 && (aux.index() % 6) != 4) {
        aux = aux.next().opp();
    }
    return {map(), aux.index() / 6};
}

vertex_handle halfedge_handle::from_vh() const
{
    return prev().to_vh();
}

edge_handle halfedge_handle::eh() const
{
    auto halfedge_index = index() % 6;
    if (halfedge_index < 3) {
        auto cell_index = index() / 6;
        return {map(), 3 * cell_index + halfedge_index};
    }
    else {
        return opp().eh();
    }
}

halfedge_handle halfedge_handle::opp() const
{
    auto cell_index = index() / 6;
    auto row = cell_index / map().cols();
    auto col = cell_index % map().cols();
    auto new_halfedge_index = (index() + 3) % 6;
    switch (new_halfedge_index) {
        case 0: {
            auto new_col = (col + 1) % map().cols();
            return {map(), (map().cols() * row + new_col) * 6 + new_halfedge_index};
        }
        case 1: {
            auto new_row = (row + map().rows() - 1) % map().rows();
            auto new_col = col;
            if (new_row % 2 == 0) {
                new_col = (col + 1) % map().cols();
            }
            return {map(), (map().cols() * new_row + new_col) * 6 + new_halfedge_index};
        }
        case 2: {
            return {map(), (map().cols() * row + col) * 6 + new_halfedge_index};
        }
        case 3: {
            auto new_col = (col + map().cols() - 1) % map().cols();
            return {map(), (map().cols() * row + new_col) * 6 + new_halfedge_index};
        }
        case 4: {
            auto new_row = (row + 1) % map().rows();
            auto new_col = col;
            if (new_row % 2 == 1) {
                new_col = (col + map().cols() - 1) % map().cols();
            }
            return {map(), (map().cols() * new_row + new_col) * 6 + new_halfedge_index};
        }
        case 5: {
            return {map(), (map().cols() * row + col) * 6 + new_halfedge_index};
        }
    }
    assert(false);
    return *this; // never reached
}

halfedge_handle halfedge_handle::next() const
{
    auto subcell_index = index() / 3;
    auto new_halfedge_index = (index() + 1) % 3;
    return {map(), subcell_index * 3 + new_halfedge_index};
}

halfedge_handle halfedge_handle::prev() const
{
    auto subcell_index = index() / 3;
    auto new_halfedge_index = (index() + 2) % 3;
    return {map(), subcell_index * 3 + new_halfedge_index};
}

}
