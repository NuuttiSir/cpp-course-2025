#pragma once

#include "Image.hpp"

extern "C"
{
#include <cgif.h>
}

namespace pixelmancy {
class ColorPallette;
struct Frame;
class ColorMatcher;

class Gif
{
public:
    explicit Gif(std::shared_ptr<ColorMatcher> colorMatcher);
    virtual ~Gif();

    /**
     *   Save the gif to the file path
     *   @param filePath path to save the gif
     */
    bool save(const std::string& filePath);

    /**
     *   Add a frame to the gif
     *   @param frame image to add as a frame
     *   @param delay delay in milliseconds
     */
    void addFrame(const Image& frame, uint16_t delay = DEFAULT_FRAME_DELAY);

    /**
     * Close the gif
     */
    void close();

private:
    std::size_t reduceGlobalColorPalette();
    int init(const std::string& filePath);
    uint8_t* getPaletteData();
    void initGIFConfig(CGIF_Config* pConfig, char* path, uint16_t width, uint16_t height, uint8_t* pPalette, uint16_t numColors);
    void initFrameConfig(CGIF_FrameConfig* pConfig, std::vector<uint8_t>& imageDataVec, uint16_t delay);
    void loadFrames();
    void globalColorPaletteGeneration();

    std::shared_ptr<ColorMatcher> m_colorMatcher;
    std::vector<IndexMapPtr> m_localToGlobalMappings;
    std::vector<Frame> _frames;
    int _width = 0;
    int _height = 0;
    IndexMapPtr m_globalToReducedColorMap;
    CGIF* pGIF = nullptr;
    std::unique_ptr<ColorPallette> m_globalPallette;
    bool m_colorReduced = false;
    std::unique_ptr<ColorPallette> m_reducedGlobalPallette;
};

} // namespace pixelmancy
