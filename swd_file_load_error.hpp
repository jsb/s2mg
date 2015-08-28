#pragma once

#include <stdexcept>

namespace s2mg {

struct swd_file_load_error : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}
