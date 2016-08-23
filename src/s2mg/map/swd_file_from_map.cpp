#include "swd_file_from_map.hpp"

#include <s2mg/map/map.hpp>

#include <cstring>

namespace s2mg {

swd_file swd_file_from_map(const map& _map)
{
    const auto& dim = _map.dimensions;
    swd_file result{dim.cols(), dim.rows()};

    std::strcpy(result.header.title, "Test World"); // TODO: name from map
    result.header.terrain_type = 0; // greenland
    result.header.num_players = 0; // TODO: player data from map
    std::strcpy(result.header.author, "s2mg");
    for (int player_id = 0; player_id < 7; ++player_id) {
        result.header.hq_x[player_id] = 0xFFFF; // invalid, TODO: player data from map
        result.header.hq_y[player_id] = 0xFFFF; // invalid, TODO: player data from map
    }

    // Block 0: altitude
    for (auto vh : dim.vertices()) {
        result.blocks[0].data[vh.index()] = 0x0A;
    }

    return result;
}

}