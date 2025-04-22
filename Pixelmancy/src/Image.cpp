#include "Image.hpp"

#include <lodepng.h>
#include "Log.hpp"
#include "PNG.hpp"

#include <memory>

namespace pixelmancy {

Image Image::mergeImages(const Image& firstImage, const Image& secondImag)
{
    if (firstImage.isEmpty() && secondImag.isEmpty())
    {
        return *(new Image(0, 0));
    }
    if (firstImage.isEmpty())
    {
        return *(new Image(secondImag));
    }
    if (secondImag.isEmpty())
    {
        return *(new Image(firstImage));
    }

    auto maxWidth = std::max(firstImage.getWidth(), secondImag.getWidth());
    auto maxHeight = std::max(firstImage.getHeight(), secondImag.getHeight());

    Image* img = new Image(maxWidth, maxHeight);

    for (int i = 0; i < firstImage.getWidth(); i++)
    {
        for (int j = 0; j < firstImage.getHeight(); j++)
        {
            Color firstColor = firstImage(i, j);
            (*img)(i, j) = firstColor;
        }
    }

    for (int i = 0; i < secondImag.getWidth(); i++)
    {
        for (int j = 0; j < secondImag.getHeight(); j++)
        {
            const Color secondColor = secondImag(i, j);
            (*img)(i, j) = secondColor;
        }
    }
    return *(img);
}

Image::Image(int width, int height, const Color& background) : m_imageDimensions({width, height})
{
    if (m_imageDimensions.isEmpty())
    {
        return;
    }
    auto index = m_colorPalette.addColor(background);
    auto size = static_cast<std::size_t>(m_imageDimensions.width * m_imageDimensions.height);
    m_pixels.resize(size, index);
}

Image::Image(const Image& other) : m_imageDimensions(other.m_imageDimensions), m_pixels(other.m_pixels), m_colorPalette(other.m_colorPalette)
{
}

Image::Image(Image&& other) noexcept
 : m_imageDimensions(other.m_imageDimensions), m_pixels(std::move(other.m_pixels)), m_colorPalette(std::move(other.m_colorPalette))
{
    // It is not necessary to reset the other object, but the author of this code
    // prefers to do so to make it clear that the object is in a moved-from state.
    other.m_colorPalette.reset();
}

bool Image::operator==(const Image& other) const
{
    if (m_imageDimensions != other.m_imageDimensions)
    {
        return false;
    }

    if (m_imageDimensions.isEmpty() && other.m_imageDimensions.isEmpty())
    {
        return true;
    }

    if (m_pixels.size() != other.m_pixels.size())
    {
        return false;
    }

    for (size_t i = 0; i < m_pixels.size(); i++)
    {
        if (m_pixels[i] != other.m_pixels[i])
        {
            return false;
        }
    }

    if (m_colorPalette != other.m_colorPalette)
    {
        return false;
    }

    return true;
}

void Image::removeAlphaChannel()
{
    m_colorPalette.convertToRGBfromRGBA();
}

void Image::blueShift()
{
    m_colorPalette.blueShift();
}

Image Image::resize(double percentage) const
{
    const int width = static_cast<int>(std::ceil(m_imageDimensions.width * percentage));
    const int height = static_cast<int>(std::ceil(m_imageDimensions.height * percentage));
    if (width == m_imageDimensions.width && height == m_imageDimensions.height)
    {
        return *this;
    }
    if (width <= 0 || height <= 0)
    {
        P_LOG_ERROR() << "Invalid image dimensions after resize\n";
        return *(new Image(0, 0));
    }
    double scaleX = 2;
    double scaleY = 2;
    Image newImage(width, height, WHITE);
    // P_LOG_DEBUG() << fmt::format("Resizing image from {}x{} to {}x{}\n", m_imageDimensions.width, m_imageDimensions.height, width, height);
    // P_LOG_DEBUG() << fmt::format("Width scale : {} Height scale : {}\n", widthScale, heightScale);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // Calculate the corresponding pixel in the original image
            int originalX = static_cast<int>(std::floor(i * scaleX));
            int originalY = static_cast<int>(std::floor(j * scaleY));
            const Color& clr = (*this)(originalY, originalX);
            newImage(j, i) = clr;
        }
    }
    return newImage;
}

bool Image::replaceColorPalette(const ColorPallette& colorPalette)
{
    if (m_colorPalette.size() != colorPalette.size())
    {
        return false;
    }
    m_colorPalette = colorPalette;
    return true;
}

bool Image::replaceColorPalette(ColorPallette&& colorPalette)
{
    P_LOG_DEBUG() << "ColorPallette&& colorPalette\n";
    if (m_colorPalette.size() != colorPalette.size())
    {
        P_LOG_DEBUG() << "Color palettes dementions does not match\n";
        return false;
    }
    m_colorPalette = std::move(colorPalette);
    return true;
}

bool Image::reduceColorPalette(std::size_t expectedPaletteSize)
{
    ColorPallette colorPalette = m_colorPalette;
    const std::vector<int>& oldToNewIndexMap = m_colorPalette.reduceColors(expectedPaletteSize);

    if (oldToNewIndexMap.empty())
    {
        P_LOG_DEBUG() << "Color palette already reduced\n";
        return false;
    }

    for (size_t i = 0; i < m_pixels.size(); i++)
    {
        m_pixels[i] = static_cast<uint16_t>(oldToNewIndexMap[m_pixels[i]]);
    }

    // P_LOG_DEBUG() << fmt::format("Reduced color palette from {} to {}\n", colorPalette.size(), m_colorPalette.size());
    return true;
}

ColorPallette&& Image::colorPalette()
{
    return std::move(m_colorPalette);
}

const ColorPallette& Image::getColorPalette()
{
    return m_colorPalette;
}

int Image::getWidth() const
{
    return m_imageDimensions.width;
}

std::size_t Image::size() const
{
    return m_imageDimensions.width * m_imageDimensions.height;
}

int Image::getHeight() const
{
    return m_imageDimensions.height;
}

std::vector<uint8_t> Image::getImageData() const
{
    std::vector<uint8_t> data;
    data.reserve(m_pixels.size());
    for (auto clrIndex : m_pixels)
    {
        data.push_back(static_cast<uint8_t>(clrIndex));
    }
    return data;
}

bool Image::isEmpty() const
{
    return m_imageDimensions.isEmpty();
}

Image Image::loadFromFile(const std::string& filePath)
{
    std::vector<unsigned char> buffer;
    std::vector<unsigned char> image;
    unsigned w, h;

    lodepng::load_file(buffer, filePath);
    lodepng::State state;

    state.decoder.color_convert = 1;
    state.info_raw.colortype = LCT_RGBA;
    state.info_raw.bitdepth = 8;

    P_LOG_INFO() << "Loading image from file: " << filePath << "\n";
    P_LOG_TRACE() << "buffer.size() " << buffer.size() << "\n";
    unsigned error = lodepng::decode(image, w, h, state, buffer);

    if (error)
    {
        P_LOG_ERROR() << "decoder error " << error << " : " << lodepng_error_text(error) << "\n";
        throw std::runtime_error(lodepng_error_text(error));
    }
    P_LOG_TRACE() << fmt::format("Image size - width: {} height: {}\n", w, h);
    P_LOG_TRACE() << fmt::format("Color type : {}\n", static_cast<int>(state.info_png.color.colortype));
    P_LOG_TRACE() << fmt::format("Bit depth : {}\n", static_cast<int>(state.info_png.color.bitdepth));
    P_LOG_TRACE() << fmt::format("Palette size : {}\n", static_cast<int>(state.info_png.color.palettesize));

    pixelmancy::Image img(static_cast<int>(w), static_cast<int>(h));

    for (int j = 0; j < img.getHeight(); j++)
    {
        for (int i = 0; i < img.getWidth(); i++)
        {
            const auto imageIndex = static_cast<std::size_t>((j * img.getWidth() + i) * 4);
            const unsigned char red = image[imageIndex];
            const unsigned char green = image[imageIndex + 1];
            const unsigned char blue = image[imageIndex + 2];
            const unsigned char alpha = image[imageIndex + 3];
            const Color clr_(red, green, blue, alpha);
            img(j, i) = clr_;
        }
    }

    return img;
}

bool Image::save(const std::string& filePath) const
{
    PNG png(*this);
    return png.save(filePath);
}

} // namespace pixelmancy
