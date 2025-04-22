#include <CircleObject.hpp>
#include <Image.hpp>
#include <Line.hpp>
#include <SquareObject.hpp>
#include <catch2/catch_test_macros.hpp>

#include "common.hpp"

TEST_CASE("50x50 circle", "[shapes]")
{
    auto circle = pixelmancy::graphics::CircleObject(50, 2, pixelmancy::MAGENTA, pixelmancy::GREEN);

    SECTION("When the image is smaller than circle")
    {
        pixelmancy::Image img(50, 50);
        circle.drawOn(img);
        img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/circle_quarter.png");
    }

    SECTION("When the image is exactly the size of the circle")
    {
        pixelmancy::Image img(100, 100);
        circle.drawOn(img);
        img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/circle_exact.png");
    }

    SECTION("CircleObject in the middle")
    {
        pixelmancy::Image img(500, 500);
        circle.setPosition({250, 250});
        circle.drawOn(img);
        img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/circle_in_the_middle.png");
    }
}

TEST_CASE("50x100 square", "[shapes]")
{
    auto square = pixelmancy::graphics::SquareObject({50, 50}, 2, pixelmancy::MAGENTA, pixelmancy::GREEN);

    SECTION("When the image is smaller than circle")
    {
        pixelmancy::Image img(25, 25);
        square.drawOn(img);
        img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/square_quarter.png");
    }

    SECTION("When the image is exactly the size of the circle")
    {
        pixelmancy::Image img(100, 100);
        square.drawOn(img);
        img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/square_exact.png");
    }
}

TEST_CASE("Circles in rotation", "[shapes]")
{
    auto circle = pixelmancy::graphics::CircleObject(10, 2, pixelmancy::MAGENTA, pixelmancy::GREEN);
    SECTION("Cicles in a circle")
    {
        pixelmancy::Image img(550, 550);
        pixelmancy::sizei2d center = {.width = 275, .height = 275};
        int radius = 240;
        double theta = 0;
        for (int i = 0; i < 360; i += 10)
        {
            theta = i * M_PI / 180;
            int x = center.width + radius * cos(theta);
            int y = center.height + radius * sin(theta);
            circle.setPosition({x, y});
            circle.drawOn(img);
        }
        img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/circles_in_a_circle.png");
    }
}
