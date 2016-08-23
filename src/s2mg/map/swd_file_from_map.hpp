#pragma once

#include <s2mg/swd/swd_file.hpp>

namespace s2mg {

struct map;

swd_file swd_file_from_map(const map& _map);

}