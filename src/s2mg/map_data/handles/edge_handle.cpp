#include "edge_handle.hpp"
#include "halfedge_handle.hpp"

namespace s2mg {

halfedge_handle edge_handle::heh(int _dir) const
{
    auto cell_index = index() / 3;
    auto edge_index = index() % 3;
    auto halfedge_index = edge_index * 2;
    halfedge_handle result{map(), 3 * cell_index + halfedge_index};
    if (_dir == 0) {
        return result;
    }
    else {
        return result.opp();
    }
}

}
