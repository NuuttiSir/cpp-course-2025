#pragma once

#include "Common.hpp"
#include "IDrawable.hpp"

namespace pixelmancy::graphics {

/**
 * DrawableObject class that represents a drawable object
 */
class DrawableObject : public IDrawable
{
public:
    DrawableObject();

    /**
     * Set the position of the object
     * @param position position of the object
     */
    void setPosition(const Point& position);

    /**
     * Get the rotation angle of the object
     * @return rotation angle of the object
     */
    void setAngle(float angle);

    /**
     * Get the position of the object
     * @return position of the object
     */
    const Point& getPosition() const;

    /**
     * Get the rotation angle of the object
     * @return rotation angle of the object
     */
    float getAngle() const;

    /**
     * Helper function to know if function is imeplemented
     * by subclasses
     * @param image image to draw the object on
     */
    void drawOn(Image& image) const override;

    /**
    Get object type
    */
    virtual ObjectType getObjectType() const;

protected:
    Point m_position = {0, 0};
    float m_angle = 0.0f;
};

} // namespace pixelmancy::graphics
