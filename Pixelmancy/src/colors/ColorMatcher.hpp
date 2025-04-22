#pragma once

#include <set>
#include "ColorSpaceDistance.hpp"

namespace pixelmancy {

struct Color;

class ColorMatcher
{
public:
    ColorMatcher();
    ~ColorMatcher() = default;
    ColorMatcher(const ColorMatcher&) = delete;
    ColorMatcher& operator=(const ColorMatcher&) = delete;

    /**
     *   Get the nearest color to the color
     *   @param clr color to get the nearest color to
     *   @return nearest color
     */
    const Color& getNearestColor(const Color& clr) const;

private:
    std::set<ColorSpaceDistance, DistanceComparator> m_clrDistanceSet;
};

} // namespace pixelmancy