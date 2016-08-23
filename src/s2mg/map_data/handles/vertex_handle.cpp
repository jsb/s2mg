#include "vertex_handle.hpp"
#include "halfedge_handle.hpp"
#include "face_handle.hpp"
#include "../iterators/circulator_ranges.hpp"

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

vertex_vertex_range vertex_handle::adjacent_vertices() const
{
    return vertex_vertex_range{*this};
}

vertex_face_range vertex_handle::incident_faces() const
{
    return vertex_face_range{*this};
}

vertex_halfedge_range vertex_handle::incident_halfedges() const
{
    return vertex_halfedge_range{*this};
}

vertex_edge_range vertex_handle::incident_edges() const
{
    return vertex_edge_range{*this};
}

coord vertex_handle::to_coord() const
{
    return {index() % map().cols(), index() / map().cols()};
}

}
