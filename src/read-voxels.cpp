#include "read-voxels.h"

gl::Size gl::readSize(const std::string &path) {
    std::ifstream in_file{path, std::ios::in};
    if (!in_file.is_open()) {
        throw std::runtime_error{"Can't open file"};
    }

    std::size_t width, height, depth;
    in_file >> width >> height >> depth;

    in_file.close();

    return gl::Size{width, height, depth};
}

gl::Spacing gl::readSpacing(const std::string &path) {
    std::ifstream in_file{path, std::ios::in};
    if (!in_file.is_open()) {
        throw std::runtime_error{"Can't open file"};
    }

    float x, y, z;
    in_file >> x >> y >> z;

    in_file.close();

    return gl::Spacing{x, y, z};
}