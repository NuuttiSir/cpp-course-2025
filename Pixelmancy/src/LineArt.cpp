#include "LineArt.hpp"

#include "colors/Color.hpp"

namespace pixelmancy::graphics {

LineArt::LineArt(const Color& color = BLACK) : m_lineColor(std::make_unique<Color>(color))
{
}

void LineArt::setLineColor(const Color& clr)
{
    m_lineColor = std::make_unique<Color>(clr);
}

} // namespace pixelmancy::graphics
