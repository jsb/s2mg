#pragma once

#include "map_handle.hpp"

namespace s2mg {

class halfedge_handle;

class edge_handle : public map_handle
{
public:
    constexpr edge_handle(const map_dimensions& _map, std::size_t _index) :
        map_handle(_map, _index)
    {
    }

    halfedge_handle heh(int _dir) const;
};

}
