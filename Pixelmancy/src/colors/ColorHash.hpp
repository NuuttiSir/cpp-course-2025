#pragma once

#include <functional>
#include "Color.hpp"

namespace std {
template <>
struct hash<pixelmancy::Color>
{
    std::size_t operator()(const pixelmancy::Color& k) const
    {
        return k.hash();
    }
};
} // namespace std