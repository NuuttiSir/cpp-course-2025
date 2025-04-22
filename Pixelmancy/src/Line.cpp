#include "Line.hpp"

#include "Image.hpp"

namespace pixelmancy::graphics {

Line::Line(const Point& pointA, const Point& pointB, const Color& color) : LineArt(color), m_pointA(std::move(pointA)), m_pointB(std::move(pointB))
{
}

void Line::drawOn(Image& image) const
{
    int x0 = m_pointA.x;
    int y0 = m_pointA.y;
    const int x1 = m_pointB.x;
    const int y1 = m_pointB.y;

    const int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    const int sx = (x0 < x1) ? 1 : -1;
    const int sy = (y0 < y1) ? 1 : -1;
    int error = dx - dy;

    while (true)
    {
        if (x0 >= 0 && x0 < image.getWidth() && y0 >= 0 && y0 < image.getHeight())
        {
            image(x0, y0) = *m_lineColor;
        }

        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        int e2 = 2 * error;
        if (e2 >= -dy)
        {
            error -= dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            error += dx;
            y0 += sy;
        }
    }
}

} // namespace pixelmancy::graphics
