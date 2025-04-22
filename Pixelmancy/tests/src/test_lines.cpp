#include <CircleObject.hpp>
#include <Image.hpp>
#include <Line.hpp>
#include <SquareObject.hpp>
#include <catch2/catch_test_macros.hpp>

#include "Circle.hpp"
#include "common.hpp"

TEST_CASE("Test a normal line", "[lines]")
{
    auto line = pixelmancy::graphics::Line({0, 2}, {10, 2}, pixelmancy::MAGENTA);
    pixelmancy::Image img(5, 10);
    line.drawOn(img);
    img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/simple_line.png");
}

TEST_CASE("Test a rotated thick line", "[lines]")
{
    auto line = pixelmancy::graphics::Line({0, 2}, {10, 5}, pixelmancy::MAGENTA);
    pixelmancy::Image img(20, 20);
    line.drawOn(img);
    img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/simple_roated_line.png");
}

TEST_CASE("Test a simple line circle", "[lines]")
{
    auto circle = pixelmancy::graphics::Circle({50, 50}, 20, pixelmancy::MAGENTA);
    pixelmancy::Image img(100, 100);
    circle.drawOn(img);
    img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/simple_circle.png");
}