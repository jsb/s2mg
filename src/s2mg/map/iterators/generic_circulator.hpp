#pragma once

#include "../handles.hpp"

namespace s2mg {

class generic_end_circulator
{
};

template<typename NavigationPolicy>
class generic_circulator
{
public:
    using navigation_policy = NavigationPolicy;

    explicit generic_circulator(const typename NavigationPolicy::input_handle& _input) :
        initial_heh_(NavigationPolicy::initialize(_input)),
        heh_(initial_heh_)
    {
    }

    generic_circulator& operator++()
    {
        heh_ = NavigationPolicy::advance(heh_);
        if (heh_ == initial_heh_) {
            ++num_cycles_;
        }
    }

    typename NavigationPolicy::output_handle operator*() const
    {
        return NavigationPolicy::access(heh_);
    }

    bool operator==(const generic_end_circulator&) const
    {
        return num_cycles_ >= 1;
    }

    bool operator!=(const generic_end_circulator& _rhs) const
    {
        return !operator==(_rhs);
    }

private:
    halfedge_handle initial_heh_;
    halfedge_handle heh_;
    int num_cycles_ = 0;
};

}
