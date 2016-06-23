#pragma once

#include "iterators.hpp"

namespace s2mg {

class map_dimensions;

template<typename HandleType>
class handle_range
{
public:
    using iterator_type = handle_iterator<HandleType>;

    handle_range(const map_dimensions& _map, std::size_t _first_index, std::size_t _last_index) :
        first_(_map, _first_index),
        last_(_map, _last_index)
    {
    }

    iterator_type begin() const { return first_; }
    iterator_type end()   const { return last_;  }

private:
    iterator_type first_;
    iterator_type last_;
};

class vertex_handle;
class face_handle;
class halfedge_handle;
class edge_handle;

using vertex_range   = handle_range<vertex_handle>;
using face_range     = handle_range<face_handle>;
using halfedge_range = handle_range<halfedge_handle>;
using edge_range     = handle_range<edge_handle>;

}
