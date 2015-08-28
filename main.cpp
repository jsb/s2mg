#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include "swd_file.hpp"

int main()
{
    s2mg::swd_file f{"/Users/jsb/Resources/Dosbox/SIEDLER2/WORLDS/TEST123_.SWD"};
    std::cout << "title: " << f.header.title << std::endl;
    std::cout << "display_width: " << f.header.display_width << std::endl;
    std::cout << "display_height: " << f.header.display_height << std::endl;
    std::cout << "terrain_type: " << f.header.terrain_type << std::endl;
    std::cout << "num_players: " << f.header.num_players << std::endl;
    std::cout << "author: " << f.header.author << std::endl;
    std::cout << "width: " << f.header.width << std::endl;
    std::cout << "height: " << f.header.height << std::endl;

    auto& tri_block_up = f.blocks[1];
    //auto& tri_block_down = f.blocks[2];

    srand(time(nullptr));
    for (uint16_t y = 0; y < f.header.height; ++y) {
        std::printf("%2d: ", y);
        for (uint16_t x = 0; x < f.header.width; ++x) {
            auto index = y * f.header.width + x;
            std::printf("%2x", tri_block_up.data[index]);
        }
        std::printf("\n");
    }

    f.write("/Users/jsb/Resources/Dosbox/SIEDLER2/WORLDS/TESTOUT_.SWD");
}
