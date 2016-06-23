#pragma once

#include "map_handle.hpp"

namespace s2mg {

class halfedge_handle;
class vertex_handle;

class face_vertex_range;
class face_face_range;
class face_halfedge_range;
class face_edge_range;

class face_handle : public map_handle
{
public:
    constexpr face_handle(const map_dimensions& _map, std::size_t _index) :
        map_handle(_map, _index)
    {
    }

    //! One arbitrary halfedge that lies within the face
    halfedge_handle heh() const;

    //! One arbitrary vertex that is incident to the face
    vertex_handle vh() const;

    face_vertex_range   incident_vertices() const;
    face_face_range     adjacent_faces() const;
    face_halfedge_range incident_halfedges() const;
    face_edge_range     incident_edges() const;
};

}
