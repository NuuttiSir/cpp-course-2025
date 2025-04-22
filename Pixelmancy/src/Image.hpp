#pragma once

#include <logger/Log.hpp>
#include "ColorPalette.hpp"
#include "colors/Color.hpp"
#include "sizei2d.hpp"

namespace pixelmancy {
class Image
{
public:
    static Image loadFromFile(const std::string& filePath);

    static Image mergeImages(const Image& firstImage, const Image& secondImage);

    Image(int width, int height, const Color& background = BLACK);
    Image(const Image& other);
    Image(Image&& other) noexcept;

    ~Image() = default;

    bool isEmpty() const;
    void removeAlphaChannel();
    void blueShift();
    Image resize(double percentage) const;
    bool replaceColorPalette(const ColorPallette& colorPalette);
    bool replaceColorPalette(ColorPallette&& colorPalette);

    ColorPallette&& colorPalette();
    const ColorPallette& getColorPalette();

    bool operator==(const Image& other) const;

    Color operator()(int row, int column) const
    {
        std::size_t index = static_cast<size_t>(row * m_imageDimensions.width + column);
        Color clr = m_colorPalette.getColor(m_pixels[index]);
        return clr;
    }

    int getWidth() const;
    int getHeight() const;
    std::size_t size() const;

    std::vector<uint8_t> getImageData() const;
    bool reduceColorPalette(std::size_t expectedPaletteSize);
    bool save(const std::string& filePath) const;

    class Proxy
    {
    public:
        Proxy(std::vector<uint16_t>& pixels, int index, ColorPallette& colorPalette)
         : m_pixels(pixels), m_index(static_cast<unsigned int>(index)), m_colorPalette(colorPalette)
        {
        }

        Proxy& operator=(const Color& color)
        {
            auto clrIndex = m_colorPalette.addColor(color);
            if (m_index >= m_pixels.size())
            {
                P_LOG_DEBUG() << "Resizing pixels vector to " << m_pixels.size() * 2 << logger::endl;
                m_pixels.resize(m_pixels.size() * 2, clrIndex);
            }
            m_pixels[m_index] = clrIndex;
            return *this;
        }

        bool operator==(const Color& color) const
        {
            const Color& clr = m_colorPalette.getColor(m_pixels[m_index]);
            return clr == color;
        }

        operator Color() const
        {
            if (m_index >= m_pixels.size())
            {
                P_LOG_ERROR() << "Index out of bounds" << logger::endl;
                return {};
            }
            Color clr = m_colorPalette.getColor(m_pixels[m_index]);
            return clr;
        }

    private:
        std::vector<uint16_t>& m_pixels;
        unsigned int m_index;
        ColorPallette& m_colorPalette;
    };

    Proxy operator()(int row, int column)
    {
        int index = row * m_imageDimensions.width + column;
        return {m_pixels, index, m_colorPalette};
    }

private:
    sizei2d m_imageDimensions;
    std::vector<uint16_t> m_pixels;
    ColorPallette m_colorPalette;
};
} // namespace pixelmancy