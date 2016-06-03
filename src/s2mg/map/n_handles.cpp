#include "n_handles.hpp"

namespace s2mg {

template<> std::size_t n_handles<vertex_handle>  (const map_dimensions& _map) { return _map.n_vertices();  }
template<> std::size_t n_handles<face_handle>    (const map_dimensions& _map) { return _map.n_faces();     }
template<> std::size_t n_handles<halfedge_handle>(const map_dimensions& _map) { return _map.n_halfedges(); }
template<> std::size_t n_handles<edge_handle>    (const map_dimensions& _map) { return _map.n_edges();     }

}
