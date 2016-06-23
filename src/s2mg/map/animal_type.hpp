#pragma once

#include <cstdint>

namespace s2mg {

enum class animal_type : uint8_t
{
    rabbit = 0x01,
    fox    = 0x02,
    stag   = 0x03,
    roe    = 0x04,
    duck   = 0x05,
    sheep  = 0x06,
};

}
