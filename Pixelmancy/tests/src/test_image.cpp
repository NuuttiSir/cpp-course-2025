#include <Image.hpp>
#include <PNG.hpp>
#include <catch2/catch_test_macros.hpp>

#include "common.hpp"

TEST_CASE("[image] Image 2x2 image", "[image]")
{
    pixelmancy::Image img(1, 1);

    REQUIRE(img.getWidth() == 1);
    REQUIRE(img.getHeight() == 1);
}

TEST_CASE("[image] Image width and height", "[image]")
{
    pixelmancy::Image img(10, 20);

    REQUIRE(img.getWidth() == 10);
    REQUIRE(img.getHeight() == 20);
}

TEST_CASE("[image] Image RGB pixel", "[image]")
{
    pixelmancy::Image img(3, 3, pixelmancy::WHITE);

    // first row
    for (int i = 0; i < 3; i++)
    {
        img(0, i) = pixelmancy::RED;
    }
    // second row
    for (int i = 0; i < 3; i++)
    {
        img(1, i) = pixelmancy::GREEN;
    }
    // third row
    for (int i = 0; i < 3; i++)
    {
        img(2, i) = pixelmancy::BLUE;
    }

    pixelmancy::PNG pngSaver(img);
    pngSaver.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/rgb.png");
    auto loadedImage = pixelmancy::Image::loadFromFile(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/rgb"
                                                                                       ".png");
    for (int i = 0; i < 3; i++)
    {
        pixelmancy::Color clr = loadedImage(0, i);
        REQUIRE(clr == pixelmancy::RED);
    }
    for (int i = 0; i < 3; i++)
    {
        pixelmancy::Color clr = loadedImage(1, i);
        REQUIRE(clr == pixelmancy::GREEN);
    }
    for (int i = 0; i < 3; i++)
    {
        pixelmancy::Color clr = loadedImage(2, i);
        REQUIRE(clr == pixelmancy::BLUE);
    }

    pixelmancy::PNG imageSaver(loadedImage);
    imageSaver.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/rb_rgb.png");
}

TEST_CASE("[image] Image RGB 5,10 pixel", "[image]")
{
    const int width = 5;
    const int height = 10;
    pixelmancy::Image img(width, height, pixelmancy::WHITE);

    // first row red
    for (int i = 0; i < width; i++)
    {
        img(0, i) = pixelmancy::RED;
    }
    // second row green
    for (int i = 0; i < width; i++)
    {
        img(1, i) = pixelmancy::GREEN;
    }
    // third row blue
    for (int i = 0; i < width; i++)
    {
        img(2, i) = pixelmancy::BLUE;
    }
    // fourth row black
    for (int i = 0; i < width; i++)
    {
        img(3, i) = pixelmancy::BLACK;
    }
    // fifth row red
    for (int i = 0; i < width; i++)
    {
        img(4, i) = pixelmancy::RED;
    }
    // last row red
    for (int i = 0; i < width; i++)
    {
        img(9, i) = pixelmancy::RED;
    }

    pixelmancy::PNG pngSaver(img);
    pngSaver.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/rgb_5_10.png");

    auto loadedImage = pixelmancy::Image::loadFromFile(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/rgb_5_10.png");

    for (int i = 0; i < width; i++)
    {
        REQUIRE(loadedImage(0, i) == pixelmancy::RED);
    }
    for (int i = 0; i < width; i++)
    {
        REQUIRE(loadedImage(1, i) == pixelmancy::GREEN);
    }
    for (int i = 0; i < width; i++)
    {
        REQUIRE(loadedImage(2, i) == pixelmancy::BLUE);
    }
    for (int i = 0; i < width; i++)
    {
        REQUIRE(loadedImage(3, i) == pixelmancy::BLACK);
    }
    for (int i = 0; i < width; i++)
    {
        REQUIRE(loadedImage(4, i) == pixelmancy::RED);
    }
    for (int i = 0; i < width; i++)
    {
        REQUIRE(loadedImage(9, i) == pixelmancy::RED);
    }

    loadedImage.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/rb_rgb_5_10.png");
}

TEST_CASE("[image] Image RGB large pixel", "[image]")
{
    const int width = 70;
    const int height = 998;
    pixelmancy::Image img(width, height, pixelmancy::WHITE);

    pixelmancy::ColorPallette pallette = img.getColorPalette();

    // first row red
    for (int i = 0; i < width; i++)
    {
        img(0, i) = pixelmancy::RED;
    }
    // second row green
    for (int i = 0; i < width; i++)
    {
        img(1, i) = pixelmancy::GREEN;
    }
    // third row blue
    for (int i = 0; i < width; i++)
    {
        img(2, i) = pixelmancy::BLUE;
    }
    // fourth row black
    for (int i = 0; i < width; i++)
    {
        img(3, i) = pixelmancy::BLACK;
    }
    // fifth row red
    for (int i = 0; i < width; i++)
    {
        img(4, i) = pixelmancy::RED;
    }
    // last row red
    for (int i = 0; i < width; i++)
    {
        img(height - 1, i) = pixelmancy::RED;
    }

    pixelmancy::ColorPallette pallette2 = img.getColorPalette();

    img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/rgb_726_998.png");

    auto loadedImage = pixelmancy::Image::loadFromFile(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/rgb_726_998.png");

    pixelmancy::ColorPallette pallette3 = loadedImage.getColorPalette();

    for (int i = 0; i < width; i++)
    {
        REQUIRE(loadedImage(0, i) == pixelmancy::RED);
    }
    for (int i = 0; i < width; i++)
    {
        REQUIRE(loadedImage(1, i) == pixelmancy::GREEN);
    }
    for (int i = 0; i < width; i++)
    {
        REQUIRE(loadedImage(2, i) == pixelmancy::BLUE);
    }
    for (int i = 0; i < width; i++)
    {
        REQUIRE(loadedImage(3, i) == pixelmancy::BLACK);
    }
    for (int i = 0; i < width; i++)
    {
        REQUIRE(loadedImage(4, i) == pixelmancy::RED);
    }

    for (int j = 5; j < height - 2; j++)
    {
        for (int i = 0; i < width; i++)
        {
            REQUIRE(loadedImage(j, i) == pixelmancy::WHITE);
        }
    }

    for (int i = 0; i < width; i++)
    {
        REQUIRE(loadedImage(height - 1, i) == pixelmancy::RED);
    }

    loadedImage.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/rb_rgb_726_998.png");
}

TEST_CASE("[image] Image one 5,5 pixel", "[image]")
{
    pixelmancy::Image img(10, 20);

    pixelmancy::Color color(10, 20, 30, 40);
    pixelmancy::Color color_copy(10, 20, 30, 40);
    img(5, 5) = color;

    pixelmancy::Color color_wrong(11, 20, 30, 40);

    pixelmancy::Color def;

    pixelmancy::Color color_get = img(5, 5);
    REQUIRE(color_get == color_copy);
    REQUIRE(color_get != color_wrong);

    img(5, 5) = def;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            REQUIRE(img(i, j) == def);
        }
    }
}

TEST_CASE("[image] Image all default pixel", "[image]")
{
    pixelmancy::Image img(10, 20);
    pixelmancy::Color def;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            REQUIRE(img(i, j) == def);
        }
    }
}

TEST_CASE("[image] Image all given background", "[image]")
{
    pixelmancy::Color red(255, 0, 0, 255);
    pixelmancy::Image img(10, 20, red);

    pixelmancy::Color red_copy(255, 0, 0, 255);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            REQUIRE(img(i, j) == red_copy);
        }
    }
}

TEST_CASE("[image] RED image save", "[image]")
{
    pixelmancy::Color red(255, 0, 0, 255);
    pixelmancy::Image img(10, 20, red);

    {
        img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/red.png");
    }

    pixelmancy::Color red_copy(255, 0, 0, 255);
    for (int i = 0; i < img.getHeight(); i++)
    {
        for (int j = 0; j < img.getWidth(); j++)
        {
            REQUIRE(img(i, j) == red_copy);
        }
    }
}

TEST_CASE("[image] Load image from file", "[image]")
{
    auto img = pixelmancy::Image::loadFromFile(TEST_DATA_INPUT_IMAGE_FOLDER + "/naruto.png");
    auto palette = img.getColorPalette();
    img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/rb_naruto.png");
}

TEST_CASE("[image] Load image from file - PNG RGBA to RGB", "[image]")
{
    auto img = pixelmancy::Image::loadFromFile(TEST_DATA_INPUT_IMAGE_FOLDER + "naruto.png");
    img.removeAlphaChannel();
    auto palette = img.getColorPalette();
    img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/rb_naruto_RGB.png");
}

TEST_CASE("[image] Load image from file - reduce to 256 colors", "[image]")
{
    auto img = pixelmancy::Image::loadFromFile(TEST_DATA_INPUT_IMAGE_FOLDER + "naruto.png");
    // img.blueShift();
    img.removeAlphaChannel();
    img.reduceColorPalette(256);
    img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/rb_naruto_reduced_256_Colors.png");
}

TEST_CASE("[image] reduce image size to 100x100", "[image]")
{
    auto img = pixelmancy::Image::loadFromFile(TEST_DATA_INPUT_IMAGE_FOLDER + "dog.png");
    img.save(TEST_DATA_OUTPUT_IMAGE_FOLDER + "/same_dog.png");
}
