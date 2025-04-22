#include "PNG.hpp"

#include "Image.hpp"
#include "Log.hpp"
#include "lodepng.h"

namespace pixelmancy {

PNG::PNG(const Image& image) : _image(image)
{
}

PNG::~PNG() = default;

bool PNG::save(const std::string& filePath)
{
    std::vector<unsigned char> image;
    const auto width = static_cast<uint16_t>(_image.getWidth());
    const auto height = static_cast<uint16_t>(_image.getHeight());
    image.reserve(static_cast<std::size_t>(width * height * 4));

    for (uint16_t x = 0; x < _image.getHeight(); x++)
    {
        for (uint16_t y = 0; y < _image.getWidth(); y++)
        {
            const Color& clr_ = _image(x, y);
            image.push_back(clr_.red);
            image.push_back(clr_.green);
            image.push_back(clr_.blue);
            image.push_back(clr_.alpha);
        }
    }

    lodepng::State state;
    state.encoder.auto_convert = 1;
    std::vector<unsigned char> png;
    unsigned error = lodepng::encode(png, image, width, height, state);
    if (error)
    {
        P_LOG_ERROR() << fmt::format("encoder error {}: {}\n", error, lodepng_error_text(error));
        return false;
    }
    return lodepng::save_file(png, filePath) == 0;
}

} // namespace pixelmancy
