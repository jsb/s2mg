#pragma once

#include "../map_dimensions.hpp"

namespace s2mg {

class map_handle
{
public:
    constexpr map_handle(const map_dimensions& _map, std::size_t _index) :
        map_(&_map),
        index_(_index)
    {
    }

    constexpr const map_dimensions& map() const { return *map_; }
    constexpr std::size_t index() const { return index_; }

    constexpr bool operator==(const map_handle& _rhs) const
    {
        return (map_ == _rhs.map_) && (index_ == _rhs.index_);
    }

    constexpr bool operator!=(const map_handle& _rhs) const
    {
        return !operator==(_rhs);
    }

private:
    const map_dimensions* map_;
    std::size_t index_;
};

}
