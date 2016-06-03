#pragma once

#include "map_dimensions.hpp"

namespace s2mg {

template<typename H> std::size_t n_handles(const map_dimensions&);
template<> std::size_t n_handles<vertex_handle>  (const map_dimensions& _map);
template<> std::size_t n_handles<face_handle>    (const map_dimensions& _map);
template<> std::size_t n_handles<halfedge_handle>(const map_dimensions& _map);
template<> std::size_t n_handles<edge_handle>    (const map_dimensions& _map);

}
