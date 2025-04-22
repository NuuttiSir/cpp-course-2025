#include "Gif.hpp"
#include <cstddef>

#include "Common.hpp"
#include "CommonConfig.hpp"
#include "Log.hpp"
#include "colors/ColorMatcher.hpp"

namespace pixelmancy {

Gif::Gif(std::shared_ptr<ColorMatcher> colorMatcher)
 : m_colorMatcher(colorMatcher), m_globalPallette(std::make_unique<ColorPallette>()), m_globalToReducedColorMap(std::make_unique<IndexMap>())
{
}

Gif::~Gif()
{
    close();
}

void Gif::close()
{
    if (pGIF)
    {
        cgif_close(pGIF);
    }
    m_localToGlobalMappings.clear();
}

int Gif::init(const std::string& filePath)
{
    char* file_path = const_cast<char*>(filePath.c_str());
    CGIF_Config gConfig;
    auto numColors = static_cast<uint16_t>(m_globalPallette->size());
    if (numColors > MAX_COLORS_SUPPORTED_IN_GIF)
    {
        numColors = static_cast<uint16_t>(reduceGlobalColorPalette());
    }
    uint8_t* pallet = getPaletteData();
    initGIFConfig(&gConfig, file_path, static_cast<uint16_t>(_width), static_cast<uint16_t>(_height), pallet, numColors);
    pGIF = cgif_newgif(&gConfig);
    if (pGIF == nullptr)
    {
        P_LOG_ERROR() << "Failed to create gif" << "\n";
        delete[] pallet;
        return -1;
    }
    delete[] pallet;
    return 0;
}

std::size_t Gif::reduceGlobalColorPalette()
{
    std::vector<Color> Colors = m_globalPallette->getColors();
    m_reducedGlobalPallette = std::make_unique<ColorPallette>();

    int index = 0;
    for (auto& clr : Colors)
    {
        auto const& nearestClr = m_colorMatcher->getNearestColor(clr);
        auto const newMappedIndex = m_reducedGlobalPallette->addColor(nearestClr);
        m_globalToReducedColorMap->insert(std::make_pair(index, newMappedIndex));
        index++;
    }
    m_colorReduced = true;
    return m_reducedGlobalPallette->size();
}

void Gif::addFrame(const Image& frame, uint16_t delay)
{
    if (_width < frame.getWidth())
    {
        _width = frame.getWidth();
    }
    if (_height < frame.getHeight())
    {
        _height = frame.getHeight();
    }
    _frames.push_back({delay, frame});
}

bool Gif::save(const std::string& filePath)
{
    globalColorPaletteGeneration();
    m_globalPallette->convertToRGBfromRGBA();
    int result = init(filePath);
    if (result != 0)
    {
        P_LOG_ERROR() << "Failed to initialize GIF encoder. Exiting without saving GIF" << "\n";
        return false;
    }
    loadFrames();
    // close();
    return result == 0;
}

void Gif::globalColorPaletteGeneration()
{
    for (auto& frame : _frames)
    {
        const auto& palette = frame.image.getColorPalette();
        IndexMapPtr localToGlobalColorMap = m_globalPallette->merge(palette);
        m_localToGlobalMappings.push_back(std::move(localToGlobalColorMap));
    }
    P_LOG_DEBUG() << "Global Color palette size: " << m_globalPallette->size() << "\n";
}

void Gif::initGIFConfig(CGIF_Config* pConfig, char* path, uint16_t width, uint16_t height, uint8_t* pPalette, uint16_t numColors)
{
    memset(pConfig, 0, sizeof(CGIF_Config));
    pConfig->width = width;
    pConfig->height = height;
    pConfig->pGlobalPalette = pPalette;
    pConfig->numGlobalPaletteEntries = numColors;
    pConfig->path = path;
    pConfig->attrFlags = CGIF_ATTR_IS_ANIMATED;
}

uint8_t* Gif::getPaletteData()
{
    uint16_t numColors = static_cast<uint16_t>(m_globalPallette->size());
    if (m_colorReduced)
    {
        numColors = static_cast<uint16_t>(m_reducedGlobalPallette->size());
    }
    std::vector<uint8_t> aPalette;
    if (m_colorReduced)
    {
        aPalette = m_reducedGlobalPallette->getPaletteData();
    }
    else
    {
        aPalette = m_globalPallette->getPaletteData();
    }
    uint8_t* pallet = new uint8_t[numColors * 3];
    auto endPoint = static_cast<uint16_t>(numColors * 3);
    for (std::size_t i = 0; i < endPoint; i++)
    {
        pallet[i] = aPalette[i];
    }
    return pallet;
}

void Gif::initFrameConfig(CGIF_FrameConfig* pConfig, std::vector<uint8_t>& imageDataVec, uint16_t delay)
{
    memset(pConfig, 0, sizeof(CGIF_FrameConfig));
    pConfig->delay = delay;
    pConfig->pImageData = imageDataVec.data();
}

void Gif::loadFrames()
{
    if (pGIF == nullptr)
    {
        P_LOG_ERROR() << "GIF not initialized\n";
        return;
    }
    size_t frameIndex = 0;
    for (auto& frame : _frames)
    {
        // load frame pointing to zero index of color palette
        std::vector<uint8_t> imageDataVec(static_cast<std::size_t>(_width * _height));

        const std::vector<uint8_t>& frameData = frame.image.getImageData();
        IndexMapPtr& localToGlobalColorMap = m_localToGlobalMappings[frameIndex];

        // load frame data to imageDataVec
        for (int i = 0; i < frame.image.getHeight(); i++)
        {
            for (int j = 0; j < frame.image.getWidth(); j++)
            {
                auto imagePixelIndex = static_cast<std::size_t>(i * frame.image.getWidth() + j);
                uint16_t globalIndex = static_cast<uint16_t>((*localToGlobalColorMap)[frameData[imagePixelIndex]]);
                if (m_colorReduced)
                {
                    globalIndex = (*m_globalToReducedColorMap)[globalIndex];
                }
                const auto index = static_cast<std::size_t>(i * _width + j);
                imageDataVec[index] = static_cast<uint8_t>(globalIndex);
            }
        }

        CGIF_FrameConfig fConfig;
        initFrameConfig(&fConfig, imageDataVec, frame.delay);
        cgif_addframe(pGIF, &fConfig);

        frameIndex++;
    }
}

} // namespace pixelmancy
