#include "face_handle.hpp"
#include "halfedge_handle.hpp"
#include "vertex_handle.hpp"

namespace s2mg {

halfedge_handle face_handle::heh() const
{
    return {map(), index() * 3};
}

vertex_handle face_handle::vh() const
{
    return {map(), index() / 2};
}

}
