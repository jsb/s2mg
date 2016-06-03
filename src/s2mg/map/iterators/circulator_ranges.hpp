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
        return {input_};
    }

    generic_end_circulator end() const
    {
        return {};
    }

private:
    input_handle input_;
};


#define S2MG_MAKE_CIRCULATOR_RANGE(name_stem) \
    class name_stem ## _range : public circulator_range<name_stem ## _circulator> { \
    public: \
        name_stem ## _range(const circulator_range::input_handle& _input) : circulator_range(_input) {} \
        name_stem ## _range(const name_stem ## _range&) = default; \
    };

S2MG_MAKE_CIRCULATOR_RANGE(vertex_vertex)
S2MG_MAKE_CIRCULATOR_RANGE(vertex_face)
S2MG_MAKE_CIRCULATOR_RANGE(vertex_halfedge)
S2MG_MAKE_CIRCULATOR_RANGE(vertex_edge)

S2MG_MAKE_CIRCULATOR_RANGE(face_vertex)
S2MG_MAKE_CIRCULATOR_RANGE(face_face)
S2MG_MAKE_CIRCULATOR_RANGE(face_halfedge)
S2MG_MAKE_CIRCULATOR_RANGE(face_edge)

#undef S2MG_MAKE_CIRCULATOR_RANGE

}
