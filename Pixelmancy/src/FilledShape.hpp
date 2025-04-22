#pragma once

#include "DrawableObject.hpp"
#include "colors/Color.hpp"

namespace pixelmancy::graphics {

/**
 * FilledShape class that represents a shape with a fill color and an outline color
 */
class FilledShape : public DrawableObject
{
public:
    FilledShape(const Color& fillColor, const Color& outlineColor, int outlineWidth);
    ~FilledShape() override = default;

    /**
     * Set the width of the outline
     * @param width width of the outline
     */
    void setOutlineWidth(int width);

    /**
     * Set the fill color of the shape
     * @param clr fill color
     */
    void setFillColor(const Color& clr);

    /**
     * Set the outline color of the shape
     * @param clr outline color
     */
    void setOutlineColor(const Color& clr);

    /**
     * Get the width of the outline
     * @return width of the outline
     */
    int getOutlineWidth() const;

    /**
     * Get the fill color of the shape
     * @return fill color
     */
    Color getFillColor() const;

    /**
     * Get the outline color of the shape
     * @return outline color
     */
    Color getOutlineColor() const;

protected:
    Color m_fillColor;
    Color m_outlineColor;
    int m_outlineWidth;
};

} // namespace pixelmancy::graphics
