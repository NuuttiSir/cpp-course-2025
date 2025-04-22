#pragma once

#include "Common.hpp"
#include "FilledShape.hpp"
#include "Image.hpp"
#include "sizei2d.hpp"

namespace pixelmancy {
struct Color;
}

namespace pixelmancy::graphics {

class SquareObject : public FilledShape
{
public:
    SquareObject(sizei2d size2d, int outlineWidth, const Color& fillColor, const Color& outlineColor = BLACK);
    void drawOn(Image& image) const;
    
private:
    sizei2d m_size2d = {0, 0};
};

} // namespace pixelmancy::graphics
