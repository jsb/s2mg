#pragma once

#include <cstddef>
#include <cassert>

namespace s2mg {

class map_dimensions
{
public:
    map_dimensions(std::size_t _cols, std::size_t _rows) :
        cols_(_cols),
        rows_(_rows)
    {
        assert(rows_ % 2 == 0);
    }

    std::size_t cols() const { return cols_; }
    std::size_t rows() const { return rows_; }

    std::size_t n_vertices() const { return rows_ * cols_; }
    std::size_t n_faces() const { return 2 * n_vertices(); }
    std::size_t n_edges() const { return 3 * n_vertices(); }
    std::size_t n_halfedges() const { return 2 * n_edges(); }

private:
    std::size_t cols_;
    std::size_t rows_;
};

}
