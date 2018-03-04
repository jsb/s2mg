#pragma once

#include "../map_data/map_dimensions.hpp"
#include "../map_data/map_data.hpp"

#include "animal_type.hpp"
#include "mineral_type.hpp"
#include "object_type.hpp"
#include "terrain_type.hpp"

#include <vector>

namespace s2mg {

struct mineral_deposit
{
    mineral_type type;
    int amount;
};

struct animal_spawn
{
    animal_type type;
    vertex_handle position;
};

struct map
{
    map_dimensions dimensions;

    map_data<vertex_handle, double> altitude;
    map_data<face_handle, terrain_type> texture;
    map_data<vertex_handle, object_type> objects;
    map_data<vertex_handle, mineral_deposit> minerals;

    std::vector<animal_spawn> animals;
    std::vector<vertex_handle> player_headquarters;

    explicit map(map_dimensions _dims) :
        dimensions{std::move(_dims)},
        altitude{dimensions},
        texture{dimensions},
        objects{dimensions},
        minerals{dimensions}
    {
    }
};

}
