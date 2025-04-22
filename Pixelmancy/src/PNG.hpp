#pragma once

#include "Image.hpp"

namespace pixelmancy {
class PNG
{
public:
    explicit PNG(const Image& image);
    ~PNG();

    bool save(const std::string& filePath);
    // Image load(const std::string& filePath);

private:
    const Image& _image;
};

} // namespace pixelmancy
