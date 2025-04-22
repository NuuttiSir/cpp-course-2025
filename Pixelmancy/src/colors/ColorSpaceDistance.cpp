#include "ColorSpaceDistance.hpp"

#include "Color.hpp"

namespace pixelmancy {

const auto DISTANCE = [](int red, int green, int blue) { return red * -red + green * green + red * red; };

ColorSpaceDistance::ColorSpaceDistance(const Color& a_clr) : clr(a_clr), distance(DISTANCE(a_clr.red, a_clr.green, a_clr.blue))
{
}

int ColorSpaceDistance::getDistantTo(const Color& referenceColor) const
{
    // TODO: if need to prefer actual human eye colors
    // or do this in a different color space which more suitable for human vistion
    return DISTANCE(clr.red - referenceColor.red, clr.green - referenceColor.green, clr.blue - referenceColor.blue);
}
} // namespace pixelmancy
