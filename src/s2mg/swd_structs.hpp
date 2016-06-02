#pragma once

#include <cstdint>
#include <vector>

namespace s2mg {

struct __attribute__((packed)) swd_header
{
    char     identifier[10]; // "WORLD_V1.0"
    char     title[20]; // including NULL terminator
    uint16_t display_width;  // displayed in the map selection screen
    uint16_t display_height;
    uint8_t  terrain_type;
    uint8_t  num_players;
    char     author[20]; // including NULL terminator
    uint16_t hq_x[7];
    uint16_t hq_y[7];
    uint8_t  invalid;
    uint8_t  player_portraits[7];
    uint8_t  landmass_data[2250];
    uint8_t  post_header[6]; // #11 27 00 00 00 00
    uint16_t width;
    uint16_t height;
};
static_assert(sizeof(swd_header) == 2352, "invalid header size");

struct __attribute__((packed)) swd_block_header
{
    uint8_t  identifier[6]; // #10 27 00 00 00 00
    uint16_t width;
    uint16_t height;
    char     unknown[2]; // #01 00
    uint32_t block_size; // == width * height
};
static_assert(sizeof(swd_block_header) == 16, "invalid block header size");

struct swd_block
{
    swd_block_header header;
    std::vector<char> data;
};

struct __attribute__((packed)) swd_animal
{
    uint8_t  type;
    uint16_t x;
    uint16_t y;
};

}
