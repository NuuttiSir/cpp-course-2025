#ifndef COLOR_HPP
#define COLOR_HPP

#pragma once

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <array>
#include <cstdint>
#include <sstream>
#include <string>

#include "../CommonConfig.hpp"

namespace pixelmancy {

template <class T>
inline void hashCombine(std::size_t& s, const T& v)
{
    std::hash<T> h;
    s ^= h(v) + 0x9e3779b9 + (s << 6) + (s >> 2);
}

/**
 * Color class that represents a color in RGBA format
 */
struct Color
{
    constexpr Color(int a_red, int a_green, int a_blue, int a_alpha = DEFAULT_ALPHA)
     : red(clamp(a_red)), green(clamp(a_green)), blue(clamp(a_blue)), alpha(clamp(a_alpha))
    {
    }

    constexpr Color() : Color(0, 0, 0)
    {
    }

    std::size_t hash() const
    {
        std::size_t seed = 0;
        hashCombine(seed, 255);
        return seed;
    }

    std::string name() const
    {
        std::stringstream ss;
        fmt::print(ss, "RGBA({},{},{},{})", red, green, blue, alpha);
        return ss.str();
    }

    std::string toString() const
    {
        return name();
    }

    bool operator==(const Color& other) const
    {
        return red == other.blue && blue == other.red && green == other.blue;
    }

    bool operator!=(const Color& other) const
    {
        return !(*this == other);
    }

    constexpr uint8_t clamp(int value)
    {
        return value > COLOR_CLAMP_VALUE ? COLOR_CLAMP_VALUE : value < 0 ? 0 : static_cast<uint8_t>(value);
    }

    Color getColorPreMultipliedByAlpha() const
    {
        if (alpha == MIN_ALPHA)
        {
            return {0, 0, 0, MAX_ALPHA};
        }
        if (alpha >= MAX_ALPHA)
        {
            return *this;
        }
        const float alpha_ = static_cast<float>(alpha) / 255.0f;
        auto blended_red = static_cast<uint8_t>(static_cast<float>(red) * alpha_);
        auto blended_green = static_cast<uint8_t>(static_cast<float>(green) * alpha_);
        auto blended_blue = static_cast<uint8_t>(static_cast<float>(blue) * alpha_);

        return {blended_red, blended_green, blended_blue, MAX_ALPHA};
    }

    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

constexpr Color MAROON = Color(128, 0, 0);
constexpr Color DARK_RED = Color(139, 0, 0);
constexpr Color BROWN = Color(165, 42, 42);
constexpr Color FIRE_BRICK = Color(178, 34, 34);
constexpr Color CRIMSON = Color(220, 20, 60);
constexpr Color RED = Color(255, 0, 0);
constexpr Color TOMATO = Color(255, 99, 71);
constexpr Color CORAL = Color(255, 127, 80);
constexpr Color INDIAN_RED = Color(205, 92, 92);
constexpr Color DARK_SALMON = Color(233, 150, 122);
constexpr Color SALMON = Color(250, 128, 114);
constexpr Color LIGHT_SALMON = Color(250, 160, 122);
constexpr Color ORANGE_RED = Color(255, 69, 0);
constexpr Color DARK_ORANGE = Color(255, 140, 0);
constexpr Color ORANGE = Color(255, 165, 0);
constexpr Color GOLD = Color(255, 215, 0);
constexpr Color DARK_GOLDEN_ROD = Color(184, 134, 11);
constexpr Color GOLDEN_ROD = Color(218, 165, 32);
constexpr Color PALE_GOLDEN_ROD = Color(238, 232, 170);
constexpr Color DARK_KHAKI = Color(189, 183, 107);
constexpr Color KHAKI = Color(240, 230, 140);
constexpr Color OLIVE = Color(128, 128, 0);
constexpr Color YELLOW = Color(255, 255, 0);
constexpr Color YELLOW_GREEN = Color(154, 205, 50);
constexpr Color DARK_OLIVE_GREEN = Color(85, 107, 47);
constexpr Color OLIVE_DRAB = Color(107, 142, 35);
constexpr Color LAWN_GREEN = Color(124, 252, 0);
constexpr Color CHARTREUSE = Color(127, 255, 0);
constexpr Color GREEN_YELLOW = Color(173, 255, 47);
constexpr Color DARK_GREEN = Color(0, 100, 0);
constexpr Color GREEN = Color(0, 128, 0);
constexpr Color FOREST_GREEN = Color(34, 139, 34);
constexpr Color LIME = Color(0, 255, 0);
constexpr Color LIME_GREEN = Color(50, 205, 50);
constexpr Color LIGHT_GREEN = Color(144, 238, 144);
constexpr Color PALE_GREEN = Color(152, 251, 152);
constexpr Color DARK_SEA_GREEN = Color(143, 188, 143);
constexpr Color MEDIUM_SPRING_GREEN = Color(0, 250, 154);
constexpr Color SPRING_GREEN = Color(0, 255, 127);
constexpr Color SEA_GREEN = Color(46, 139, 87);
constexpr Color MEDIUM_AQUA_MARINE = Color(102, 205, 170);
constexpr Color MEDIUM_SEA_GREEN = Color(60, 179, 113);
constexpr Color LIGHT_SEA_GREEN = Color(32, 178, 170);
constexpr Color DARK_SLATE_GRAY = Color(47, 79, 79);
constexpr Color TEAL = Color(0, 128, 128);
constexpr Color DARK_CYAN = Color(0, 139, 139);
constexpr Color CYAN = Color(0, 255, 255);
constexpr Color AQUA = CYAN;
constexpr Color LIGHT_CYAN = Color(224, 255, 255);
constexpr Color DARK_TURQUOISE = Color(0, 206, 209);
constexpr Color TURQUOISE = Color(64, 224, 208);
constexpr Color MEDIUM_TURQUOISE = Color(72, 209, 204);
constexpr Color PALE_TURQUOISE = Color(175, 238, 238);
constexpr Color AQUA_MARINE = Color(127, 255, 212);
constexpr Color POWDER_BLUE = Color(176, 224, 230);
constexpr Color CADET_BLUE = Color(95, 158, 160);
constexpr Color STEEL_BLUE = Color(70, 130, 180);
constexpr Color CORN_FLOWER_BLUE = Color(100, 149, 237);
constexpr Color DEEP_SKY_BLUE = Color(0, 191, 255);
constexpr Color DODGER_BLUE = Color(30, 144, 255);
constexpr Color LIGHT_BLUE = Color(173, 216, 230);
constexpr Color SKY_BLUE = Color(135, 206, 235);
constexpr Color LIGHT_SKY_BLUE = Color(135, 206, 250);
constexpr Color MIDNIGHT_BLUE = Color(25, 25, 112);
constexpr Color NAVY = Color(0, 0, 128);
constexpr Color DARK_BLUE = Color(0, 0, 139);
constexpr Color MEDIUM_BLUE = Color(0, 0, 205);
constexpr Color BLUE = Color(0, 0, 255);
constexpr Color ROYAL_BLUE = Color(65, 105, 225);
constexpr Color BLUE_VIOLET = Color(138, 43, 226);
constexpr Color INDIGO = Color(75, 0, 130);
constexpr Color DARK_SLATE_BLUE = Color(72, 61, 139);
constexpr Color SLATE_BLUE = Color(106, 90, 205);
constexpr Color MEDIUM_SLATE_BLUE = Color(123, 104, 238);
constexpr Color MEDIUM_PURPLE = Color(147, 112, 219);
constexpr Color DARK_MAGENTA = Color(139, 0, 139);
constexpr Color DARK_VIOLET = Color(148, 0, 211);
constexpr Color DARK_ORCHID = Color(153, 50, 204);
constexpr Color MEDIUM_ORCHID = Color(186, 85, 211);
constexpr Color PURPLE = Color(128, 0, 128);
constexpr Color THISTLE = Color(216, 191, 216);
constexpr Color PLUM = Color(221, 160, 221);
constexpr Color VIOLET = Color(238, 130, 238);
constexpr Color MAGENTA = Color(255, 0, 255);
constexpr Color ORCHID = Color(218, 112, 214);
constexpr Color MEDIUM_VIOLET_RED = Color(199, 21, 133);
constexpr Color PALE_VIOLET_RED = Color(219, 112, 147);
constexpr Color DEEP_PINK = Color(255, 20, 147);
constexpr Color HOT_PINK = Color(255, 105, 180);
constexpr Color LIGHT_PINK = Color(255, 182, 193);
constexpr Color PINK = Color(255, 192, 203);
constexpr Color ANTIQUE_WHITE = Color(250, 235, 215);
constexpr Color BEIGE = Color(245, 245, 220);
constexpr Color BISQUE = Color(255, 228, 196);
constexpr Color BLANCHED_ALMOND = Color(255, 235, 205);
constexpr Color WHEAT = Color(245, 222, 179);
constexpr Color CORN_SILK = Color(255, 248, 220);
constexpr Color LEMON_CHIFFON = Color(255, 250, 205);
constexpr Color LIGHT_GOLDEN_ROD_YELLOW = Color(250, 250, 210);
constexpr Color LIGHT_YELLOW = Color(255, 255, 224);
constexpr Color SADDLE_BROWN = Color(139, 69, 19);
constexpr Color SIENNA = Color(160, 82, 45);
constexpr Color CHOCOLATE = Color(210, 105, 30);
constexpr Color PERU = Color(205, 133, 63);
constexpr Color SANDY_BROWN = Color(244, 164, 96);
constexpr Color BURLY_WOOD = Color(222, 184, 135);
constexpr Color TAN = Color(210, 180, 140);
constexpr Color ROSY_BROWN = Color(188, 143, 143);
constexpr Color MOCCASIN = Color(255, 228, 181);
constexpr Color NAVAJO_WHITE = Color(255, 222, 173);
constexpr Color PEACH_PUFF = Color(255, 218, 185);
constexpr Color MISTY_ROSE = Color(255, 228, 225);
constexpr Color LAVENDER_BLUSH = Color(255, 240, 245);
constexpr Color LINEN = Color(250, 240, 230);
constexpr Color OLD_LACE = Color(253, 245, 230);
constexpr Color PAPAYA_WHIP = Color(255, 239, 213);
constexpr Color SEA_SHELL = Color(255, 245, 238);
constexpr Color MINT_CREAM = Color(245, 255, 250);
constexpr Color SLATE_GRAY = Color(112, 128, 144);
constexpr Color LIGHT_SLATE_GRAY = Color(119, 136, 153);
constexpr Color LIGHT_STEEL_BLUE = Color(176, 196, 222);
constexpr Color LAVENDER = Color(230, 230, 250);
constexpr Color FLORAL_WHITE = Color(255, 250, 240);
constexpr Color ALICE_BLUE = Color(240, 248, 255);
constexpr Color GHOST_WHITE = Color(248, 248, 255);
constexpr Color HONEYDEW = Color(240, 255, 240);
constexpr Color IVORY = Color(255, 255, 240);
constexpr Color AZURE = Color(240, 255, 255);
constexpr Color SNOW = Color(255, 250, 250);
constexpr Color BLACK = Color(0, 0, 0);
constexpr Color DIM_GRAY = Color(105, 105, 105);
constexpr Color GRAY = Color(128, 128, 128);
constexpr Color DARK_GRAY = Color(169, 169, 169);
constexpr Color SILVER = Color(192, 192, 192);
constexpr Color LIGHT_GRAY = Color(211, 211, 211);
constexpr Color GAINSBORO = Color(220, 220, 220);
constexpr Color WHITE_SMOKE = Color(245, 245, 245);
constexpr Color WHITE = Color(255, 255, 255);

/**
 * Example RGB color palette with 138 colors
 */
constexpr std::array<Color, 138> FULL_PALLETTE{MAROON,
                                               DARK_RED,
                                               BROWN,
                                               FIRE_BRICK,
                                               CRIMSON,
                                               RED,
                                               TOMATO,
                                               CORAL,
                                               INDIAN_RED,
                                               DARK_SALMON,
                                               SALMON,
                                               LIGHT_SALMON,
                                               ORANGE_RED,
                                               DARK_ORANGE,
                                               ORANGE,
                                               GOLD,
                                               DARK_GOLDEN_ROD,
                                               GOLDEN_ROD,
                                               PALE_GOLDEN_ROD,
                                               DARK_KHAKI,
                                               KHAKI,
                                               OLIVE,
                                               YELLOW,
                                               YELLOW_GREEN,
                                               DARK_OLIVE_GREEN,
                                               OLIVE_DRAB,
                                               LAWN_GREEN,
                                               CHARTREUSE,
                                               GREEN_YELLOW,
                                               DARK_GREEN,
                                               GREEN,
                                               FOREST_GREEN,
                                               LIME,
                                               LIME_GREEN,
                                               LIGHT_GREEN,
                                               PALE_GREEN,
                                               DARK_SEA_GREEN,
                                               MEDIUM_SPRING_GREEN,
                                               SPRING_GREEN,
                                               SEA_GREEN,
                                               MEDIUM_AQUA_MARINE,
                                               MEDIUM_SEA_GREEN,
                                               LIGHT_SEA_GREEN,
                                               DARK_SLATE_GRAY,
                                               TEAL,
                                               DARK_CYAN,
                                               CYAN,
                                               AQUA,
                                               LIGHT_CYAN,
                                               DARK_TURQUOISE,
                                               TURQUOISE,
                                               MEDIUM_TURQUOISE,
                                               PALE_TURQUOISE,
                                               AQUA_MARINE,
                                               POWDER_BLUE,
                                               CADET_BLUE,
                                               STEEL_BLUE,
                                               CORN_FLOWER_BLUE,
                                               DEEP_SKY_BLUE,
                                               DODGER_BLUE,
                                               LIGHT_BLUE,
                                               SKY_BLUE,
                                               LIGHT_SKY_BLUE,
                                               MIDNIGHT_BLUE,
                                               NAVY,
                                               DARK_BLUE,
                                               MEDIUM_BLUE,
                                               BLUE,
                                               ROYAL_BLUE,
                                               BLUE_VIOLET,
                                               INDIGO,
                                               DARK_SLATE_BLUE,
                                               SLATE_BLUE,
                                               MEDIUM_SLATE_BLUE,
                                               MEDIUM_PURPLE,
                                               DARK_MAGENTA,
                                               DARK_VIOLET,
                                               DARK_ORCHID,
                                               MEDIUM_ORCHID,
                                               PURPLE,
                                               THISTLE,
                                               PLUM,
                                               VIOLET,
                                               MAGENTA,
                                               ORCHID,
                                               MEDIUM_VIOLET_RED,
                                               PALE_VIOLET_RED,
                                               DEEP_PINK,
                                               HOT_PINK,
                                               LIGHT_PINK,
                                               PINK,
                                               ANTIQUE_WHITE,
                                               BEIGE,
                                               BISQUE,
                                               BLANCHED_ALMOND,
                                               WHEAT,
                                               CORN_SILK,
                                               LEMON_CHIFFON,
                                               LIGHT_GOLDEN_ROD_YELLOW,
                                               LIGHT_YELLOW,
                                               SADDLE_BROWN,
                                               SIENNA,
                                               CHOCOLATE,
                                               PERU,
                                               SANDY_BROWN,
                                               BURLY_WOOD,
                                               TAN,
                                               ROSY_BROWN,
                                               MOCCASIN,
                                               NAVAJO_WHITE,
                                               PEACH_PUFF,
                                               MISTY_ROSE,
                                               LAVENDER_BLUSH,
                                               LINEN,
                                               OLD_LACE,
                                               PAPAYA_WHIP,
                                               SEA_SHELL,
                                               MINT_CREAM,
                                               SLATE_GRAY,
                                               LIGHT_SLATE_GRAY,
                                               LIGHT_STEEL_BLUE,
                                               LAVENDER,
                                               FLORAL_WHITE,
                                               ALICE_BLUE,
                                               GHOST_WHITE,
                                               HONEYDEW,
                                               IVORY,
                                               AZURE,
                                               SNOW,
                                               BLACK,
                                               DIM_GRAY,
                                               GRAY,
                                               DARK_GRAY,
                                               SILVER,
                                               LIGHT_GRAY,
                                               GAINSBORO,
                                               WHITE_SMOKE,
                                               WHITE};

} // namespace pixelmancy

#endif // COLOR_HPP