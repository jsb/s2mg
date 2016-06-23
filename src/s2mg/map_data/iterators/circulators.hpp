#pragma once

#include "generic_circulator.hpp"

namespace s2mg {

namespace navigation_policies {

struct vertex_circulation
{
    using input_handle = vertex_handle;

    static halfedge_handle initialize(const input_handle& _vh)
    {
        return _vh.heh();
    }

    static halfedge_handle advance(const halfedge_handle& _heh)
    {
        return _heh.prev().opp();
    }
};

struct face_circulation
{
    using input_handle = face_handle;

    static halfedge_handle initialize(const input_handle& _fh)
    {
        return _fh.heh();
    }

    static halfedge_handle advance(const halfedge_handle& _heh)
    {
        return _heh.next();
    }
};

struct vertex_vertex_circulation : public vertex_circulation
{
    using output_handle = vertex_handle;

    static output_handle access(const halfedge_handle& _heh)
    {
        return _heh.to_vh();
    }
};

struct vertex_face_circulation : public vertex_circulation
{
    using output_handle = face_handle;

    static output_handle access(const halfedge_handle& _heh)
    {
        return _heh.fh();
    }
};

struct vertex_halfedge_circulation : public vertex_circulation
{
    using output_handle = halfedge_handle;

    static output_handle access(const halfedge_handle& _heh)
    {
        return _heh;
    }
};

struct vertex_edge_circulation : public vertex_circulation
{
    using output_handle = edge_handle;

    static output_handle access(const halfedge_handle& _heh)
    {
        return _heh.eh();
    }
};

struct face_vertex_circulation : public face_circulation
{
    using output_handle = vertex_handle;

    static output_handle access(const halfedge_handle& _heh)
    {
        return _heh.to_vh();
    }
};

struct face_face_circulation : public face_circulation
{
    using output_handle = face_handle;

    static output_handle access(const halfedge_handle& _heh)
    {
        return _heh.opp().fh();
    }
};

struct face_halfedge_circulation : public face_circulation
{
    using output_handle = halfedge_handle;

    static output_handle access(const halfedge_handle& _heh)
    {
        return _heh;
    }
};

struct face_edge_circulation : public face_circulation
{
    using output_handle = edge_handle;

    static output_handle access(const halfedge_handle& _heh)
    {
        return _heh.eh();
    }
};

}

using vertex_vertex_circulator   = generic_circulator<navigation_policies::vertex_vertex_circulation>;
using vertex_face_circulator     = generic_circulator<navigation_policies::vertex_face_circulation>;
using vertex_halfedge_circulator = generic_circulator<navigation_policies::vertex_halfedge_circulation>;
using vertex_edge_circulator     = generic_circulator<navigation_policies::vertex_edge_circulation>;

using face_vertex_circulator     = generic_circulator<navigation_policies::face_vertex_circulation>;
using face_face_circulator       = generic_circulator<navigation_policies::face_face_circulation>;
using face_halfedge_circulator   = generic_circulator<navigation_policies::face_halfedge_circulation>;
using face_edge_circulator       = generic_circulator<navigation_policies::face_edge_circulation>;

}
