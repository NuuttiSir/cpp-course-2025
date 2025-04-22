#include <Common.hpp>
#include <Image.hpp>
#include <catch2/catch_test_macros.hpp>
#include "common.hpp"

TEST_CASE("Blue Frame", "[frame]")
{
    pixelmancy::Color blue(0, 0, 255, 255);
    pixelmancy::Image redImage(800, 600, blue);
    REQUIRE(redImage.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/test_blue_frame.png"));
}

TEST_CASE("Unknown Frame ref", "[frame]")
{
    pixelmancy::Color unknown(250, 123, 205, 255);
    pixelmancy::Image unknown_frame(800, 600, unknown);

    REQUIRE(unknown_frame.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/test_unknownImage_frame.png"));
}

TEST_CASE("Green Frame", "[frame]")
{
    pixelmancy::Color green(0, 255, 0, 255);
    pixelmancy::Image greenImage(800, 600, green);

    REQUIRE(greenImage.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/test_green_frame.png"));
}
