#pragma once

#include "map_handle.hpp"
#include "face_orientation.hpp"

namespace s2mg {

class halfedge_handle;
class face_handle;

class vertex_vertex_range;
class vertex_face_range;
class vertex_halfedge_range;
class vertex_edge_range;

class vertex_handle : public map_handle
{
public:
    constexpr vertex_handle(const map_dimensions& _map, std::size_t _index) :
        map_handle(_map, _index)
    {
    }

    //! One arbitrary outgoing halfedge handle
    halfedge_handle heh() const;

    //! One of the two faces belonging to the cell of the vertex
    face_handle fh(face_orientation _orientation) const;

    vertex_vertex_range   adjacent_vertices() const;
    vertex_face_range     incident_faces() const;
    vertex_halfedge_range incident_halfedges() const;
    vertex_edge_range     incident_edges() const;
};

}
