#include "FilledShape.hpp"

namespace pixelmancy {
namespace graphics {

FilledShape::FilledShape(const Color& fillColor, const Color& outlineColor, int outlineWidth)
 : m_fillColor(std::move(fillColor)), m_outlineColor(std::move(outlineColor)), m_outlineWidth(outlineWidth)
{
}

void FilledShape::setOutlineWidth(int width)
{
    m_outlineWidth = width;
}

void FilledShape::setFillColor(const Color& clr)
{
    m_fillColor = clr;
}

void FilledShape::setOutlineColor(const Color& clr)
{
    m_outlineColor = clr;
}

int FilledShape::getOutlineWidth() const
{
    return m_outlineWidth;
}

Color FilledShape::getFillColor() const
{
    return m_fillColor;
}

Color FilledShape::getOutlineColor() const
{
    return m_outlineColor;
}

} // namespace graphics
} // namespace pixelmancy
