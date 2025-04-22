#include "SquareObject.hpp"
#include "Image.hpp"

namespace pixelmancy::graphics {
SquareObject::SquareObject(sizei2d size2d, int outlineWidth, const Color& fillColor, const Color& outlineColor)
 : FilledShape(fillColor, outlineColor, outlineWidth), m_size2d(size2d)
{
}

void SquareObject::drawOn(Image& image) const
{
    const Point pos = m_position;
    const float angle = m_angle;
    const double radAngle = angle * (M_PI / 180.0f);

    const int xCorners[4] = {0, m_size2d.width, m_size2d.width, 0};
    const int yCorners[4] = {0, 0, m_size2d.height, m_size2d.height};

    Point rotatedCorners[4];
    for (int i = 0; i < 4; i++)
    {
        rotatedCorners[i].x = pos.x + xCorners[i] * std::cos(radAngle) - yCorners[i] * std::sin(radAngle);
        rotatedCorners[i].y = pos.y + xCorners[i] * std::sin(radAngle) + yCorners[i] * std::cos(radAngle);
    }

    int minX = std::min({rotatedCorners[0].x, rotatedCorners[1].x, rotatedCorners[2].x, rotatedCorners[3].x});
    int maxX = std::max({rotatedCorners[0].x, rotatedCorners[1].x, rotatedCorners[2].x, rotatedCorners[3].x});
    int minY = std::min({rotatedCorners[0].y, rotatedCorners[1].y, rotatedCorners[2].y, rotatedCorners[3].y});
    int maxY = std::max({rotatedCorners[0].y, rotatedCorners[1].y, rotatedCorners[2].y, rotatedCorners[3].y});

    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            bool inside = true;
            for (int i = 0; i < 4; i++)
            {
                int j = (i + 1) % 4;
                int cross = (x - rotatedCorners[i].x) * (rotatedCorners[j].y - rotatedCorners[i].y) -
                            (y - rotatedCorners[i].y) * (rotatedCorners[j].x - rotatedCorners[i].x);
                if (cross > 0)
                {
                    inside = false;
                    break;
                }
            }

            if (inside)
            {
                if (x >= 0 && x < image.getWidth() && y >= 0 && y < image.getHeight())
                {
                    image(x, y) = m_fillColor;
                }
            }
        }
    }
}


} // namespace pixelmancy::graphics
