#include <Common.hpp>
#include <Gif.hpp>
#include <PNG.hpp>
#include <catch2/catch_test_macros.hpp>
#include <memory>

#include <colors/ColorMatcher.hpp>
#include "common.hpp"

using pixelmancy::BLACK;
using pixelmancy::BLUE;
using pixelmancy::GREEN;
using pixelmancy::RED;
using pixelmancy::WHITE;

TEST_CASE("[gif] Simple GIF", "[gif]")
{
    std::shared_ptr<pixelmancy::ColorMatcher> colorMatcher = std::make_shared<pixelmancy::ColorMatcher>();
    pixelmancy::Image img(800, 600, RED);
    pixelmancy::Image img2(800, 600, GREEN);

    img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/frame1.png");
    img2.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/frame2.png");

    pixelmancy::Gif gifsaver(colorMatcher);
    gifsaver.addFrame(img);
    gifsaver.addFrame(img2);
    gifsaver.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/test.gif");
}

TEST_CASE("[gif] GIF with different size frames", "[gif]")
{
    std::shared_ptr<pixelmancy::ColorMatcher> colorMatcher = std::make_shared<pixelmancy::ColorMatcher>();
    pixelmancy::Image img_bg(800, 600, pixelmancy::SALMON);
    pixelmancy::Image img(400, 300, pixelmancy::LIGHT_SEA_GREEN);
    pixelmancy::Image img2(800, 600, pixelmancy::DARK_GREEN);

    img_bg.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/test_diff_frame_0.png");
    img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/test_diff_frame_1.png");
    img2.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/test_diff_frame_2.png");

    pixelmancy::Gif gifsaver(colorMatcher);
    gifsaver.addFrame(img_bg);
    gifsaver.addFrame(img);
    gifsaver.addFrame(img2);
    gifsaver.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/test_diff_size.gif");
}

TEST_CASE("[gif] GIF from images - one frame", "[gif]")
{
    std::shared_ptr<pixelmancy::ColorMatcher> colorMatcher = std::make_shared<pixelmancy::ColorMatcher>();
    auto dog = pixelmancy::Image::loadFromFile(TEST_DATA_INPUT_IMAGE_FOLDER + "dog.png");
    // dog->reduceColorPalette(256);
    dog.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/dog_fram1.png");

    pixelmancy::Gif gifsaver(colorMatcher);
    gifsaver.addFrame(dog);
    REQUIRE(gifsaver.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/dog.gif"));
}

TEST_CASE("[gif] GIF from images", "[gif]")
{
    std::shared_ptr<pixelmancy::ColorMatcher> colorMatcher = std::make_shared<pixelmancy::ColorMatcher>();
    auto land = pixelmancy::Image::loadFromFile(TEST_DATA_INPUT_IMAGE_FOLDER + "dog.png");
    auto cave = pixelmancy::Image::loadFromFile(TEST_DATA_INPUT_IMAGE_FOLDER + "tree.png");

    pixelmancy::ColorPallette global_pallette_0 = land.getColorPalette();
    pixelmancy::ColorPallette global_pallette_1 = cave.getColorPalette();

    pixelmancy::Gif gifsaver(colorMatcher);
    gifsaver.addFrame(land);
    gifsaver.addFrame(cave);
    REQUIRE(gifsaver.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/pixelart_dog_tree.gif"));
}

TEST_CASE("[gif] GIF from images - 2", "[gif]")
{
    std::shared_ptr<pixelmancy::ColorMatcher> colorMatcher = std::make_shared<pixelmancy::ColorMatcher>();
    auto naruto_f0 = pixelmancy::Image::loadFromFile(TEST_DATA_INPUT_IMAGE_FOLDER + "naruto.png");
    auto naruto_f1 = pixelmancy::Image::loadFromFile(TEST_DATA_INPUT_IMAGE_FOLDER + "tree.png");

    naruto_f0.removeAlphaChannel();
    naruto_f0.reduceColorPalette(200);
    naruto_f1.removeAlphaChannel();
    naruto_f1.reduceColorPalette(128);

    pixelmancy::ColorPallette global_pallette_0 = naruto_f0.getColorPalette();
    pixelmancy::ColorPallette global_pallette_1 = naruto_f1.getColorPalette();

    pixelmancy::Gif gifsaver(colorMatcher);
    gifsaver.addFrame(naruto_f0);
    gifsaver.addFrame(naruto_f1);
    REQUIRE(gifsaver.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/naruto.gif"));
}
