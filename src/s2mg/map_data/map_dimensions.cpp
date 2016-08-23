#include "map_dimensions.hpp"

#include "handles/vertex_handle.hpp"

namespace s2mg {

vertex_handle map_dimensions::vertex_at(const coord& _coord) const
{
    return {*this, _coord.y * cols_ + _coord.x};
}

}
