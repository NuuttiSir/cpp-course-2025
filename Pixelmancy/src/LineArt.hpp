#pragma once

#include <memory>
#include "IDrawable.hpp"

namespace pixelmancy {

struct Color;

namespace graphics {

class LineArt : public IDrawable
{
public:
    LineArt(const Color& color);
    void setLineColor(const Color& clr);

protected:
    std::unique_ptr<Color> m_lineColor;
};

} // namespace graphics
} // namespace pixelmancy
