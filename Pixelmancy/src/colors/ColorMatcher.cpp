
#include "ColorMatcher.hpp"

#include <Log.hpp>
#include "Color.hpp"
#include "ColorSpaceDistance.hpp"

namespace pixelmancy {

ColorMatcher::ColorMatcher()
{
    for (const auto& clr : FULL_PALLETTE)
    {
        ColorSpaceDistance clrDistance(clr);
        m_clrDistanceSet.insert(clrDistance);
    }
}

const Color& ColorMatcher::getNearestColor(const Color& clr) const
{
    ColorSpaceDistance refClr(clr);
    auto lb = m_clrDistanceSet.lower_bound(refClr);
    if (lb == m_clrDistanceSet.end())
    {
        P_LOG_TRACE() << "Not found end" << "\n";
        return WHITE;
    }

    if (lb == m_clrDistanceSet.begin())
    {
        P_LOG_TRACE() << "Found - " << (*lb).clr.name() << " for " << refClr.clr.name() << "\n";
        return BLACK;
    }

    std::advance(lb, -1);
    const ColorSpaceDistance& cdL = *lb;
    std::advance(lb, 1);
    const ColorSpaceDistance& cdU = *lb;

    int distanceToLowerBound = cdL.getDistantTo(clr);
    int distanceToUpperBound = cdU.getDistantTo(clr);

    if (distanceToLowerBound < distanceToUpperBound)
    {
        return cdL.clr;
    }
    return cdU.clr;
}

} // namespace pixelmancy
