#include "swd_file.hpp"
#include "swd_file_load_error.hpp"

#include <fstream>

namespace s2mg {

swd_file::swd_file(const std::string& _filename)
{
    read(_filename);
}

swd_file::swd_file(std::istream& _infile)
{
    read(_infile);
}

void swd_file::read(const std::string& _filename)
{
    std::ifstream f{_filename, std::ios_base::in | std::ios_base::binary};
    read(f);
}

void swd_file::read(std::istream& _infile)
{
    // Read and verify header
    _infile.read(reinterpret_cast<char*>(&header), sizeof(header));
    if (std::strncmp(header.identifier, "WORLD_V1.0", 10)) {
        throw swd_file_load_error{"Wrong file identifier"};
    }
    uint8_t post_header_magic[6] = {0x11, 0x27, 0x00, 0x00, 0x00, 0x00};
    if (!std::equal(header.post_header, header.post_header + 6, post_header_magic)) {
        throw swd_file_load_error{"Wrong post header"};
    }

    // Read and verify blocks
    uint8_t block_header_magic[6]  = {0x10, 0x27, 0x00, 0x00, 0x00, 0x00};
    for (auto& b : blocks) {
        _infile.read(reinterpret_cast<char*>(&b.header), sizeof(b.header));
        if (!std::equal(b.header.identifier, b.header.identifier + 6, block_header_magic)) {
            throw swd_file_load_error{"Wrong block header"};
        }
        if (b.header.width != header.width) {
            throw swd_file_load_error{"Block width does not match map width"};
        }
        if (b.header.height != header.height) {
            throw swd_file_load_error{"Block height does not match map height"};
        }
        if (b.header.block_size != header.width * header.height) {
            throw swd_file_load_error{"Block data size does not match block dimensions"};
        }
        b.data.resize(b.header.block_size);
        _infile.read(reinterpret_cast<char*>(b.data.data()), b.header.block_size);
    }

    // Read additional animal data until terminal 0xFF
    do {
        if (_infile.peek() == 0xFF) {
            // Found terminal character
            break;
        }
        else {
            swd_animal animal;
            _infile.read(reinterpret_cast<char*>(&animal), sizeof(animal));
            animals.push_back(std::move(animal));
        }
    }
    while (_infile);
}

void swd_file::write(const std::string& _filename) const
{
    std::ofstream f{_filename, std::ios_base::out | std::ios_base::binary};
    write(f);
}

void swd_file::write(std::ostream& _outfile) const
{
    // Write header
    _outfile.write(reinterpret_cast<const char*>(&header), sizeof(header));

    // Write all blocks
    for (const auto& b : blocks) {
        _outfile.write(reinterpret_cast<const char*>(&b.header), sizeof(b.header));
        _outfile.write(reinterpret_cast<const char*>(b.data.data()), b.header.block_size);
    }

    // Write additional animals
    for (const auto& a : animals) {
        _outfile.write(reinterpret_cast<const char*>(&a), sizeof(a));
    }

    // Write terminal 0xFF
    _outfile.put(0xFF);
}

}
