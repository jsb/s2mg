#include "gtest/gtest.h"

#include <s2mg/map/map.hpp>
#include <s2mg/swd/swd_file.hpp>
#include <s2mg/map/swd_file_from_map.hpp>

class swd_file_from_map_test : public ::testing::Test
{
protected:
    s2mg::map map{{32, 32}};
};

TEST_F(swd_file_from_map_test, create_and_write_swd) {
    for (auto fh : map.dimensions.faces()) {
        map.texture[fh] = s2mg::terrain_type::meadow;
        if (fh.index() % 7 == 0) {
            map.texture[fh] = s2mg::terrain_type::lava;
        }
    }
    s2mg::swd_file f = s2mg::swd_file_from_map(map);
    f.write("/Users/jsb/Resources/Dosbox/SIEDLER2/WORLDS/TESTOUT.SWD");
}
