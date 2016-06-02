#pragma once

#include <cstddef>
#include <iterator>

namespace s2mg {

class map_dimensions;

template<typename HandleType>
class handle_iterator : public std::iterator<std::forward_iterator_tag, HandleType>
{
public:
    handle_iterator(const map_dimensions& _map, std::size_t _index) :
        map_(&_map),
        index_(_index)
    {
    }

    HandleType operator*() const
    {
        return HandleType(*map_, index_);
    }

    handle_iterator& operator++()
    {
        ++index_;
        return *this;
    }

    bool operator==(const handle_iterator& _rhs) const
    {
        return index_ == _rhs.index_;
    }

    bool operator!=(const handle_iterator& _rhs) const
    {
        return !operator==(_rhs);
    }

private:
    const map_dimensions* map_;
    std::size_t index_;
};

class vertex_handle;
class face_handle;
class halfedge_handle;
class edge_handle;

using vertex_iterator   = handle_iterator<vertex_handle>;
using face_iterator     = handle_iterator<face_handle>;
using halfedge_iterator = handle_iterator<halfedge_handle>;
using edge_iterator     = handle_iterator<edge_handle>;

}
