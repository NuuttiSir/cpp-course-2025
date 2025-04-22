#include <catch2/catch_test_macros.hpp>
#include <colors/Color.hpp>

#include <colors/ColorSpaceDistance.hpp>

TEST_CASE("Color RGB to RGB values", "[color]")
{
    pixelmancy::Color color(10, 20, 40, 200);

    REQUIRE(color.red == 10);
    REQUIRE(color.green == 20);
    REQUIRE(color.blue == 40);
    REQUIRE(color.alpha == 200);
}

TEST_CASE("test Color distance", "[color]")
{
    pixelmancy::Color color(10, 0, 0, 200);
    pixelmancy::ColorSpaceDistance cDistance(color);
    REQUIRE(cDistance.distance == 100);

    pixelmancy::Color color2(10, 10, 10, 200);
    pixelmancy::ColorSpaceDistance cDistance2(color2);
    REQUIRE(cDistance2.distance == 300);
}
