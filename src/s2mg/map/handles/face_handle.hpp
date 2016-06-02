#pragma once

#include "map_handle.hpp"

namespace s2mg {

class halfedge_handle;
class vertex_handle;

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
};

}
