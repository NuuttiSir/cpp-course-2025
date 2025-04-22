#ifndef PIXELMANCY_DIMENSIONS_H
#define PIXELMANCY_DIMENSIONS_H

namespace pixelmancy {

struct sizei2d
{
    constexpr bool operator==(const sizei2d& other) const noexcept
    {
        return (width == other.width) && (height == other.height);
    }

    constexpr bool operator!=(const sizei2d& other) const noexcept
    {
        return width != other.width || height != other.height;
    }

    constexpr int size() const
    {
        return width * height;
    }

    constexpr bool isEmpty() const noexcept
    {
        return size() == 0;
    }

    int width;
    int height;
};

} // namespace pixelmancy

#endif // PIXELMANCY_DIMENSIONS_H
