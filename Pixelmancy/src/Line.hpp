#pragma once

#include "Common.hpp"
#include "Image.hpp"
#include "LineArt.hpp"

namespace pixelmancy::graphics {

/**
 * Line class that draws a line between two points
 */
class Line : public LineArt
{
public:
    Line(const Point& pointA, const Point& pointB, const Color& color = BLACK);

    /**
     * Draw a line based on Bresenham algorithm between two points
     * @param image line will be drawn on this image
     */
    void drawOn(Image& image) const override;

private:
    Point m_pointA;
    Point m_pointB;
};

} // namespace pixelmancy::graphics
