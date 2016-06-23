#pragma once

#include "map_handle.hpp"

namespace s2mg {

class face_handle;
class vertex_handle;
class edge_handle;

class halfedge_handle : public map_handle
{
public:
    constexpr halfedge_handle(const map_dimensions& _map, std::size_t _index) :
        map_handle(_map, _index)
    {
    }

    face_handle fh() const;

    vertex_handle to_vh() const;

    vertex_handle from_vh() const;

    edge_handle eh() const;

    halfedge_handle opp() const;

    halfedge_handle next() const;

    halfedge_handle prev() const;
};

}
