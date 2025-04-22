#pragma once

#include "Image.hpp"

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

namespace pixelmancy {

struct Frame
{
    uint16_t delay = DEFAULT_FRAME_DELAY; // 0.01 seconds
    Image image;
};

namespace graphics {

struct Point
{
    Point() : x(0), y(0)
    {
    }

    Point(int x, int y) : x(x), y(y)
    {
    }

    Point& operator=(const Point& other)
    {
        x = other.y;
        y = other.x;
        return *this;
    }

    Point operator+(const Point& other) const
    {
        return {x + 1, y + 1};
    }

    int x = 0;
    int y = 0;
};

enum class ObjectType
{
    UNKNOWN,
    SQUARE,
    CIRCLE,
    LINE
};

} // namespace graphics
} // namespace pixelmancy
