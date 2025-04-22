#include "CircleObject.hpp"
#include "Common.hpp"
#include "Image.hpp"

namespace pixelmancy::graphics {

CircleObject::CircleObject(int radius, int outlineWidth, const Color& fillColor, const Color& outlineColor)
 : FilledShape(fillColor, outlineColor, outlineWidth), m_radius(radius)
{
    m_position = {m_radius - 1, m_radius - 1};
}

void CircleObject::drawOn(Image& image) const
{
    const int startCol = m_position.y - m_radius;
    const int endCol = m_position.y + m_radius;
    const int startRow = m_position.x - m_radius;
    const int endRow = m_position.x + m_radius;
    const int circleDistance = m_radius * m_radius;
    const int innerCircleDistance = (m_radius - m_outlineWidth) * (m_radius - m_outlineWidth);
    int x = 0;
    int y = 0;
    const int imageWidth = image.getWidth();
    const int imageHeight = image.getHeight();
    for (int i = startRow; i < endRow; i++)
    {
        x = i - m_position.x;
        if (i >= imageWidth)
        {
            break;
        }
        if (i < 0)
        {
            continue;
        }
        for (int j = startCol; j < endCol; j++)
        {
            if (j >= imageHeight)
            {
                break;
            }
            if (j < 0)
            {
                continue;
            }
            y = j - m_position.y;
            const int distance = (x * x) + (y * y);
            if (distance > circleDistance)
            {
                continue;
            }
            if (m_outlineWidth > 0)
            {
                image(i, j) = distance > innerCircleDistance ? m_outlineColor : m_fillColor;
            }
            else
            {
                image(i, j) = m_fillColor;
            }
        }
    }
}

} // namespace pixelmancy::graphics
