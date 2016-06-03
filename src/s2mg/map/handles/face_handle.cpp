#include "face_handle.hpp"
#include "halfedge_handle.hpp"
#include "vertex_handle.hpp"
#include "../iterators/circulator_ranges.hpp"

namespace s2mg {

halfedge_handle face_handle::heh() const
{
    return {map(), index() * 3};
}

vertex_handle face_handle::vh() const
{
    return {map(), index() / 2};
}

face_vertex_range face_handle::incident_vertices() const
{
    return face_vertex_range{*this};
}

face_face_range face_handle::adjacent_faces() const
{
    return face_face_range{*this};
}

face_halfedge_range face_handle::incident_halfedges() const
{
    return face_halfedge_range{*this};
}

face_edge_range face_handle::incident_edges() const
{
    return face_edge_range{*this};
}

}
