#pragma once

#include <logger/Log.hpp>
#include "FilledShape.hpp"
#include "Image.hpp"
#include "colors/Color.hpp"

namespace pixelmancy::graphics {

/**
 * CircleObject class that draws a circle on an image
 * Users and provide the radius, outline width, fill color and outline color
 * to draw a circle on an image. Users can also set the position of the circle
 */
class CircleObject final : public FilledShape
{
public:
    CircleObject(int radius, int m_outlineWidth, const Color& fillColor, const Color& outlineColor);
    void drawOn(Image& image) const;
    
private:
    int m_radius;
};

} // namespace pixelmancy::graphics
