#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#pragma once

#include "Common.hpp"
#include "LineArt.hpp"

namespace pixelmancy {
namespace graphics {

/**
 * Circle class that draws a circle on an image
 * Users can provide the center, radius and color of the circle line
 * to draw a circle on an image
 */
class Circle : public LineArt
{
public:
    Circle(const Point& center, int radius, const Color& color);

    /**
     * Draw a circle based on Bresenham algorithm
     * @param image circle will be drawn on this image
     */
    void drawOn(Image& image) const override;

private:
    Point m_center;
    int m_radius;
};

} // namespace graphics
} // namespace pixelmancy

#endif // CIRCLE_HPP