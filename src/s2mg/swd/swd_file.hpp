#pragma once

#include <array>
#include <string>
#include <iostream>

#include "swd_structs.hpp"

namespace s2mg {

struct swd_file
{
public:
    swd_header header;
    std::array<swd_block, 14> blocks;
    std::vector<swd_animal> animals;

public:
    explicit swd_file(std::size_t _width, std::size_t _height);
    explicit swd_file(const std::string& _filename);
    explicit swd_file(std::istream& _infile);

    void read(const std::string& _filename);
    void read(std::istream& _infile);

    void write(const std::string& _filename) const;
    void write(std::ostream& _outfile) const;
};

}
