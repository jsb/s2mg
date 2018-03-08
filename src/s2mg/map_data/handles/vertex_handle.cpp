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

vertex_handle vertex_handle::vh_e() const
{
    auto coord = to_coord();
    coord.x = (coord.x + 1) % map().cols();
    return {map(), coord};
}

vertex_handle vertex_handle::vh_ne() const
{
    auto coord = to_coord();
    coord.x = (coord.x + (coord.x % 2)) % map().cols();
    coord.y = (coord.y + map().rows() - 1) % map().rows();
    return {map(), coord};
}

vertex_handle vertex_handle::vh_nw() const
{
    auto coord = to_coord();
    coord.x = (coord.x + map().cols() + (coord.x % 2) - 1) % map().cols();
    coord.y = (coord.y + map().rows() - 1) % map().rows();
    return {map(), coord};
}

vertex_handle vertex_handle::vh_w() const
{
    auto coord = to_coord();
    coord.x = (coord.x + map().cols() - 1) % map().cols();
    return {map(), coord};
}

vertex_handle vertex_handle::vh_sw() const
{
    auto coord = to_coord();
    coord.x = (coord.x + map().cols() + (coord.x % 2) - 1) % map().cols();
    coord.y = (coord.y + 1) % map().rows();
    return {map(), coord};
}

vertex_handle vertex_handle::vh_se() const
{
    auto coord = to_coord();
    coord.x = (coord.x + (coord.x % 2)) % map().cols();
    coord.y = (coord.y + 1) % map().rows();
    return {map(), coord};
}

coord vertex_handle::to_coord() const
{
    return {index() % map().cols(), index() / map().cols()};
}

}
