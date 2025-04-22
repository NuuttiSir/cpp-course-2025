#include "Circle.hpp"
#include <logger/Log.hpp>

namespace pixelmancy::graphics {

Circle::Circle(const Point& center, int radius, const Color& color) : LineArt(std::move(color)), m_center(std::move(center)), m_radius(radius)
{
}

// mid point circle drawing algorithm
void Circle::drawOn(Image& image) const
{
    int x = 0;
    int y = -m_radius;
    int p = -m_radius;
    while (x < -y)
    {
        if (p > 0)
        {
            y += 1;
            p += 2 * (x + y) + 1;
        }
        else
        {
            p += 2 * x + 1;
        }
        image(m_center.x + x, m_center.y + y) = *m_lineColor;
        image(m_center.x - x, m_center.y + y) = *m_lineColor;
        image(m_center.x + x, m_center.y - y) = *m_lineColor;
        image(m_center.x - x, m_center.y - y) = *m_lineColor;

        image(m_center.x + y, m_center.y + x) = *m_lineColor;
        image(m_center.x + y, m_center.y - x) = *m_lineColor;
        image(m_center.x - y, m_center.y + x) = *m_lineColor;
        image(m_center.x - y, m_center.y - x) = *m_lineColor;

        x += 1;
    }
}

} // namespace pixelmancy::graphics
