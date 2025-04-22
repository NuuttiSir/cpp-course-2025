#include "ColorPalette.hpp"

#include "Log.hpp"

#include "colors/Color.hpp"

namespace pixelmancy {

ColorPallette::ColorPallette(std::vector<Color>& colors)
{
    for (const Color& clr : colors)
    {
        addColor(clr);
    }
};

ColorPallette& ColorPallette::operator=(const ColorPallette& other)
{
    if (this != &other)
    {
        m_Colors = other.m_Colors;
        m_ColorToIndexMap = other.m_ColorToIndexMap;
        m_foundColors = other.m_foundColors;
    }
    return *this;
}

bool ColorPallette::operator==(const ColorPallette& other) const
{
    if (m_Colors.size() != other.m_Colors.size())
    {
        return false;
    }
    for (std::size_t i = 0; i < m_Colors.size(); i++)
    {
        if (m_Colors[i] != other.m_Colors[i])
        {
            return false;
        }
    }
    return true;
}

bool ColorPallette::operator!=(const ColorPallette& other) const
{
    return *this == other;
}

ColorPallette& ColorPallette::operator=(ColorPallette&& other)
{
    if (this != &other)
    {
        m_Colors = std::move(other.m_Colors);
        m_ColorToIndexMap = std::move(other.m_ColorToIndexMap);
        m_foundColors = std::move(other.m_foundColors);
        other.reset();
    }
    return *this;
}

uint16_t ColorPallette::addColor(const Color& clr)
{
    if (!m_foundColors.insert(clr).second)
    {
        return getColorIndex(clr);
    }
    m_Colors.push_back(clr);
    auto index = static_cast<uint16_t>(m_Colors.size() - 1);
    m_ColorToIndexMap.insert(std::make_pair(clr, index));
    return index;
}

uint16_t ColorPallette::addColor(Color&& clr)
{
    if (!m_foundColors.insert(clr).second)
    {
        return getColorIndex(clr);
    }
    m_Colors.push_back(clr);
    auto index = static_cast<uint16_t>(m_Colors.size() - 1);
    m_ColorToIndexMap.insert(std::make_pair(clr, index));
    return index;
}

std::vector<int> ColorPallette::reduceColors(std::size_t count)
{
    const auto totalColors = m_Colors.size();
    if (count >= totalColors)
    {
        P_LOG_INFO() << "Color count is less than or equal to requested count, no reduction needed" << logger::endl;
        return {};
    }
    std::vector<int> oldIndexToNewIndexMap;
    oldIndexToNewIndexMap.resize(totalColors);
    // check if count is power of 2 and if not make it so
    if (count & (count - 1))
    {
        count = static_cast<std::size_t>(std::pow(2, std::ceil(std::log2(count))));
        P_LOG_WARN() << "Count is not a power of 2, rounding up to " << count << logger::endl;
    }

    partialReset();

    double bitsForTotalColours = std::log2(count);
    int numBits = static_cast<int>(std::floor(bitsForTotalColours));
    unsigned char maskBit = 0xFF;
    maskBit = maskBit << (8 - numBits);

    std::vector<Color> newColors;
    newColors.reserve(count);
    for (std::size_t i = 0; i < totalColors; i++)
    {
        Color& color = m_Colors[i];
        auto newRed = color.red & maskBit;
        auto newGreen = color.green & maskBit;
        auto newBlue = color.blue & maskBit;
        Color newAverageColor(newRed, newGreen, newBlue);
        newColors.push_back(newAverageColor);
    }
    m_Colors.clear();
    std::size_t curIndex = 0;
    for (auto& color : newColors)
    {
        int newIndex = addColor(color);
        oldIndexToNewIndexMap[curIndex] = newIndex;
        curIndex++;
    }
    oldIndexToNewIndexMap.shrink_to_fit();
    P_LOG_INFO() << "Reduced color count : " << count << logger::endl;
    return oldIndexToNewIndexMap;
}

uint16_t ColorPallette::addColor(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t transparency)
{
    Color clr(red, green, blue, transparency);
    return addColor(std::move(clr));
}

uint16_t ColorPallette::getColorIndex(const Color& clr)
{
    auto found = m_ColorToIndexMap.find(clr);
    if (found != m_ColorToIndexMap.end())
    {
        return found->second;
    }
    return 0;
}

IndexMapPtr ColorPallette::merge(const ColorPallette& other)
{
    uint16_t index = 0;
    IndexMapPtr localToGlobalIndexMapPtr = std::make_unique<IndexMap>();
    for (const Color& clr : other.m_Colors)
    {
        auto mergedIndex = addColor(clr);
        localToGlobalIndexMapPtr->insert(std::make_pair(index, mergedIndex));
        index++;
    }

    return localToGlobalIndexMapPtr;
}

std::vector<uint8_t> ColorPallette::getPaletteData() const
{
    std::vector<uint8_t> paletteData;
    paletteData.reserve(size() * 3);
    for (auto& clr : m_Colors)
    {
        paletteData.push_back(clr.red);
        paletteData.push_back(clr.green);
        paletteData.push_back(clr.blue);
    }
    return paletteData;
}

void ColorPallette::partialReset()
{
    m_ColorToIndexMap.clear();
    m_foundColors.clear();
}

void ColorPallette::reset()
{
    m_ColorToIndexMap.clear();
    m_foundColors.clear();
    m_Colors.clear();
}

void ColorPallette::convertToRGBfromRGBA()
{
    std::vector<Color> newColors;
    newColors.reserve(m_Colors.size());
    partialReset();
    for (size_t i = 0; i < m_Colors.size(); i++)
    {
        auto newColor = m_Colors[i].getColorPreMultipliedByAlpha();
        newColors.push_back(newColor);
        m_ColorToIndexMap.insert(std::make_pair(newColor, i));
        m_foundColors.insert(newColor);
    }
    m_Colors = newColors;
}

void ColorPallette::blueShift()
{
    std::vector<Color> newColors;
    newColors.reserve(m_Colors.size());
    partialReset();
    for (size_t i = 0; i < m_Colors.size(); i++)
    {
        auto newColor = m_Colors[i].getColorPreMultipliedByAlpha();
        newColor.blue = newColor.green;
        newColors.push_back(newColor);
        m_ColorToIndexMap.insert(std::make_pair(newColor, i));
        m_foundColors.insert(newColor);
    }
    m_Colors = newColors;
}

} // namespace pixelmancy
