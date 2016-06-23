#pragma once

#include "circulators.hpp"

namespace s2mg {

template<typename Circulator>
class circulator_range
{
public:
    using circulator = Circulator;
    using input_handle = typename circulator::navigation_policy::input_handle;

    explicit circulator_range(const input_handle& _input) :
        input_(_input)
    {
    }

    circulator begin() const
    {
        return circulator{input_};
    }

    circulator end() const
    {
        return circulator{input_};
    }

private:
    input_handle input_;
};

class vertex_vertex_range   : public circulator_range<vertex_vertex_circulator>   { using circulator_range::circulator_range; };
class vertex_face_range     : public circulator_range<vertex_face_circulator>     { using circulator_range::circulator_range; };
class vertex_halfedge_range : public circulator_range<vertex_halfedge_circulator> { using circulator_range::circulator_range; };
class vertex_edge_range     : public circulator_range<vertex_edge_circulator>     { using circulator_range::circulator_range; };

class face_vertex_range     : public circulator_range<face_vertex_circulator>     { using circulator_range::circulator_range; };
class face_face_range       : public circulator_range<face_face_circulator>       { using circulator_range::circulator_range; };
class face_halfedge_range   : public circulator_range<face_halfedge_circulator>   { using circulator_range::circulator_range; };
class face_edge_range       : public circulator_range<face_edge_circulator>       { using circulator_range::circulator_range; };

}
