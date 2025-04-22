#pragma once

namespace pixelmancy {

class Image;

namespace graphics {

class IDrawable
{
public:
    virtual ~IDrawable() = default;
    virtual void drawOn(Image& image) const = 0;
};

} // namespace graphics
} // namespace pixelmancy
