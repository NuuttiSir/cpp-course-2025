#pragma once

namespace pixelmancy {

struct Color;

struct ColorSpaceDistance
{
    explicit ColorSpaceDistance(const Color& clr);

    int getDistantTo(const Color& referenceColor) const;

    const Color& clr;
    const int distance;
};

struct DistanceComparator
{
    bool operator()(const ColorSpaceDistance& a, const ColorSpaceDistance& b) const
    {
        return a.distance < b.distance;
    }
};

} // namespace pixelmancy
