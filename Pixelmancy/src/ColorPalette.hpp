#pragma once

#include <memory>
#include <unordered_set>
#include "CommonConfig.hpp"
#include "Log.hpp"
#include "colors/ColorHash.hpp"

namespace pixelmancy {

struct Color;

using IndexMap = std::unordered_map<uint16_t, uint16_t>;
using IndexMapPtr = std::unique_ptr<IndexMap>;

/**
 * ColorPallette class that represents a color pallette
 */
class ColorPallette
{
public:
    ColorPallette() = default;
    explicit ColorPallette(std::vector<Color>& colors);

    ~ColorPallette() = default;

    ColorPallette(const ColorPallette& other) = default;
    ColorPallette(ColorPallette&& other) = default;

    ColorPallette& operator=(const ColorPallette& other);
    ColorPallette& operator=(ColorPallette&& other);

    bool operator==(const ColorPallette& other) const;
    bool operator!=(const ColorPallette& other) const;

    /**
     * Get the color at the index
     * @param index index of the color
     * @return color at the index
     */
    Color& operator[](int index)
    {
        return m_Colors[static_cast<std::size_t>(index)];
    }

    /**
     * Get the color at the index
     * @param index index of the color
     * @return color at the index
     */
    const Color& getColor(int index) const
    {
        return m_Colors[static_cast<std::size_t>(index)];
    }

    /**
     * Replace a color in the pallette
     * @param originalColor color to replace
     * @param newColor color to replace with
     */
    void swapColor(const Color& originalColor, const Color& newColor)
    {
        const auto index = getColorIndex(originalColor);
        if (index == 0)
        {
            P_LOG_ERROR() << fmt::format("Color : {} not found in the pallette\n", originalColor.toString());
            return;
        }
        m_Colors[static_cast<std::size_t>(index)] = newColor;
    }

    /**
     * Replace a color in the pallette
     * @param index index of the color to replace
     * @param newColor color to replace with
     */
    void replaceColor(std::size_t index, const Color& newColor)
    {
        m_Colors[index] = newColor;
    }

    /**
     * Get the number of colors in the pallette
     */
    std::size_t size() const
    {
        return m_Colors.size();
    }

    /**
     * Get the colors in the pallette
     */
    const std::vector<Color>& getColors() const
    {
        return m_Colors;
    }

    /**
     * Get the colors in the pallette as a vector of uint8_t, RGBRGBRGB...
     * @return pallette data
     */
    std::vector<uint8_t> getPaletteData() const;

    /**
     * Get the index of the color
     * @param Color color to get the index of
     * @return index of the color
     */
    uint16_t getColorIndex(const Color& Color);

    /**
     * Add a color to the pallette
     * @param Color color to add
     * @return index of the color
     */
    uint16_t addColor(const Color& Color);

    /**
     * Move a color to the pallette
     * @param Color color to add
     * @return index of the color
     */
    uint16_t addColor(Color&& Color);

    /**
     * Merge the colors from another pallette
     * @param other other pallette to merge
     * @return index map of the merged pallette
     */
    IndexMapPtr merge(const ColorPallette& other);

    /**
     * Remove alpha channel from the colors
     */
    void convertToRGBfromRGBA();

    /**
     * Make blue channel same as green channel
     */
    void blueShift();

    /**
     *  Reset the pallette
     */
    void reset();

    /**
     * Reduce the number of colors in the pallette
     * @param count number of colors to reduce to
     * @return old to new index map of the reduced pallette
     * index location of the vector is the old index and the value is the new index
     */
    std::vector<int> reduceColors(std::size_t count);

private:
    uint16_t addColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t transparency = DEFAULT_ALPHA);
    void partialReset();

    std::vector<Color> m_Colors;
    std::unordered_set<Color> m_foundColors;
    std::unordered_map<Color, uint16_t> m_ColorToIndexMap;
};

} // namespace pixelmancy
