#include "swd_file_from_map.hpp"

#include <s2mg/map/map.hpp>
#include <s2mg/random.hpp>

#include <cstring>

namespace s2mg {

uint8_t encode_terrain(terrain_type _t)
{
    switch (_t) {
        case terrain_type::meadow:
            // TODO: flower variations?
            return random.choice<uint8_t>({0x08, 0x09, 0x0A});
        case terrain_type::water:
            return 0x05;
        case terrain_type::mining:
            return random.choice<uint8_t>({0x01, 0x0B, 0x0C, 0x0D});
        case terrain_type::mining_meadow:
            return 0x12;
        case terrain_type::steppe:
            return random.choice<uint8_t>({0x04, 0x80, 0x84});
        case terrain_type::steppe_meadow:
            return 0x00; // TODO: variations?
        case terrain_type::swamp:
            return 0x03;
        case terrain_type::snow:
            return 0x02;
        case terrain_type::lava:
            return 0x10;
        default:
            return encode_terrain(terrain_type::water);
    }
}

std::pair<uint8_t, uint8_t> encode_object(object_type _o)
{
    switch (_o) {
        case object_type::pine:
            return {0x30 + random.integer(8), 0xC4};
        case object_type::birch:
            return {0x70 + random.integer(8), 0xC4};
        case object_type::oak:
            return {0xB0 + random.integer(8), 0xC4};
        case object_type::palm:
            if (random.integer(2)) {
                return {0xF0 + random.integer(8), 0xC4};
            }
            else {
                return {0x30 + random.integer(8), 0xC5};
            }
        case object_type::pineapple:
            return {0x70 + random.integer(8), 0xC5};
        case object_type::cypress:
            return {0xB0 + random.integer(8), 0xC5};
        case object_type::cherry:
            return {0xF0 + random.integer(8), 0xC5};
        case object_type::fir:
            return {0x30 + random.integer(8), 0xC6};
        case object_type::granite:
            return {random.integer(0xCC, 0xCD), random.integer(0x01, 0x06)};
        case object_type::mushroom:
            return {random.choice({0x00, 0x01, 0x22}), 0xC8};
        case object_type::stone:
            return {random.integer(0x02, 0x04), 0xC8};
        case object_type::trunk:
            return {0x05, 0xC8};
        case object_type::dead_tree:
            return {0x06, 0xC8};
        case object_type::bone:
            return {random.integer(0x07, 0x08), 0xC8};
        case object_type::bush:
            return {random.integer(0x10, 0x0A), 0xC8};
        case object_type::cactus:
            return {random.integer(0x0C, 0x0D), 0xC8};
        case object_type::shrub:
            return {random.integer(0x0E, 0x14), 0xC8};
        case object_type::stalagmite:
            return {random.integer(0x18, 0x1E), 0xC8};
        case object_type::pebble:
            return {random.integer(0x25, 0x27), 0xC8};
        default:
            return {0x00, 0x00};
    }
}

swd_file swd_file_from_map(const map& _map)
{
    const auto& dim = _map.dimensions;
    swd_file result{dim.cols(), dim.rows()};

    std::strcpy(result.header.title, "Test World"); // TODO: name from map
    // TODO: player data from map
    std::strcpy(result.header.author, "s2mg");
    for (int player_id = 0; player_id < 7; ++player_id) {
        result.header.hq_x[player_id] = 0xFFFF; // invalid, TODO: player data from map
        result.header.hq_y[player_id] = 0xFFFF; // invalid, TODO: player data from map
    }

    // Block 0: Altitude
    for (auto vh : dim.vertices()) {
        result.blocks[0].data[vh.index()] = 0x0A;
    }

    // Blocks 1 and 2: Texture information
    for (auto vh : dim.vertices()) {
        result.blocks[1].data[vh.index()] = encode_terrain(_map.texture[vh.fh(face_orientation::pointing_down)]);
        result.blocks[2].data[vh.index()] = encode_terrain(_map.texture[vh.fh(face_orientation::pointing_up)]);
    }

    // Block 3: Road information (TODO: Required?)
    for (auto vh : dim.vertices()) {
        result.blocks[3].data[vh.index()] = 0x00; // "no road"
    }

    // Blocks 4 and 5: Objects
    for (auto vh : dim.vertices()) {
        auto& data4 = result.blocks[4].data[vh.index()];
        auto& data5 = result.blocks[5].data[vh.index()];
        std::tie(data4, data5) = encode_object(_map.objects[vh]);
    }

    // Block 6: Animal data
    // We use the animal list at the end of the file instead
    for (auto vh : dim.vertices()) {
        result.blocks[6].data[vh.index()] = 0x00;
    }

    // Block 7 is unknown

    // Block 8: allowed building types
    for (auto vh : dim.vertices()) {
        // TODO: calculate
        result.blocks[8].data[vh.index()] = 0x04; // big house
    }

    // Block 9 is unknown, seems to be 0x07 for all fields
    for (auto& d : result.blocks[9].data) {
        d = 0x07;
    }

    // Block 10 is unknown

    // Block 11: Resource data
    for (auto vh : dim.vertices()) {
        // TODO: resource data from map
        result.blocks[11].data[vh.index()] = 0x00; // no resources
    }

    // Block 12: Shading
    for (auto vh : dim.vertices()) {
        // TODO: compute from map altitudes
        result.blocks[12].data[vh.index()] = 0x40; // even
    }

    // Block 13 is unknown

    return result;
}

}
