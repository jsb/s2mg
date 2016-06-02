#include "vertex_handle.hpp"
#include "halfedge_handle.hpp"
#include "face_handle.hpp"

namespace s2mg {

halfedge_handle vertex_handle::heh() const
{
    return {map(), 6 * index()};
}

face_handle vertex_handle::fh(face_orientation _orientation) const
{
    if (_orientation == face_orientation::pointing_up) {
        return {map(), 2 * index()};
    }
    else {
        return {map(), 2 * index() + 1};
    }
}

}
