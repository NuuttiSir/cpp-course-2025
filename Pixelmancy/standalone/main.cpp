#include <CircleObject.hpp>
#include <Common.hpp>
#include <Gif.hpp>
#include <Image.hpp>
#include <Line.hpp>
#include <Log.hpp>
#include <SquareObject.hpp>
#include <colors/Color.hpp>
#include <colors/ColorMatcher.hpp>
#include <cstddef>
#include <cxxopts.hpp>
#include <logger/ostream_logger.hpp>
#include "config.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#ifdef _WIN32
#    include <cstdlib>
#    define WEXITSTATUS(x) x
#    define diff "fc "
#else
#    define diff "diff "
#endif

const std::string OUTPUT_FOLDER_STR = std::string(OUTPUT_FOLDER);

int virtualPoints = 0;
int totalPoints = 0;
#define PRINT_POINTS P_LOG_DEBUG() << fmt::format("Virtual points: {}/{}\n", virtualPoints, totalPoints)

#define CHECK_RETURN return totalPoints == virtualPoints ? 0 : 1

bool compareFiles(const std::string& file1, const std::string& file2)
{
#ifdef _WIN32
    // Replace forward slashes with backslashes for Windows paths
    std::string fixedFile1 = file1;
    std::replace(fixedFile1.begin(), fixedFile1.end(), '/', '\\');

    std::string fixedFile2 = file2;
    std::replace(fixedFile2.begin(), fixedFile2.end(), '/', '\\');
    std::string command = fmt::format("{} \"{}\" \"{}\"", diff, fixedFile1, fixedFile2);
#else
    std::string command = fmt::format("{} \"{}\" \"{}\"", diff, file1, file2);
#endif

    int result = WEXITSTATUS(system(command.c_str()));
    if (result == 0)
    {
        P_LOG_INFO() << "CORRECT : File : " << file1 << " and " << file2 << " are same\n";
        return true;
    }

    P_LOG_ERROR() << "File : " << file1 << " and " << file2 << " are different\n";
    return false;
}

bool fakeCompareFiles(const std::string& file1, const std::string& file2)
{
#ifdef _WIN32
    // Replace forward slashes with backslashes for Windows paths
    std::string fixedFile1 = file1;
    std::replace(fixedFile1.begin(), fixedFile1.end(), '/', '\\');

    std::string fixedFile2 = file2;
    std::replace(fixedFile2.begin(), fixedFile2.end(), '/', '\\');

    std::string command = diff + fixedFile1 + " " + fixedFile2;
#else
    std::string command = diff + file1 + " " + file2;
#endif

    int result = WEXITSTATUS(system(command.c_str()));
    if (result == 0)
    {
        P_LOG_ERROR() << "WRONG : File : " << file1 << " and " << file2 << " are same\n";
        return false;
    }

    P_LOG_INFO() << "CORRECT File : " << file1 << " and " << file2 << " are different\n";
    return true;
}

int imageResize()
{
    P_LOG_INFO() << "--- The color reduction problem START ---\n";

    auto img = pixelmancy::Image::loadFromFile(OUTPUT_FOLDER_STR + "/../tree.png");
    auto smallImage = img.resize(0.5);
    P_LOG_INFO() << "Original color count: " << img.getColorPalette().size() << "\n";
    P_LOG_INFO() << "Small image color count: " << smallImage.getColorPalette().size() << "\n";

    smallImage.save(OUTPUT_FOLDER_STR + "/resized_image.png");
    totalPoints += 1;
    if (compareFiles(OUTPUT_FOLDER_STR + "/resized_image.png", OUTPUT_FOLDER_STR + "/../resized_image.png"))
    {
        virtualPoints++;
    }

    auto smallerImage = smallImage.resize(0.25);
    smallerImage.save(OUTPUT_FOLDER_STR + "/resized_smaller_image.png");
    totalPoints += 1;
    if (compareFiles(OUTPUT_FOLDER_STR + "/resized_smaller_image.png", OUTPUT_FOLDER_STR + "/../resized_smaller_image.png"))
    {
        virtualPoints++;
    }

    auto largeImage = smallImage.resize(2);
    largeImage.save(OUTPUT_FOLDER_STR + "/resized_large_image.png");
    totalPoints += 1;
    if (compareFiles(OUTPUT_FOLDER_STR + "/resized_large_image.png", OUTPUT_FOLDER_STR + "/../resized_large_image.png"))
    {
        virtualPoints++;
    }

    smallImage.removeAlphaChannel();
    smallImage.blueShift();
    smallImage.reduceColorPalette(64);
    auto&& colorPallette = smallImage.colorPalette();
    colorPallette.swapColor(pixelmancy::Color(28, 176, 176), pixelmancy::ROSY_BROWN);
    smallImage.replaceColorPalette(std::forward<decltype(colorPallette)>(colorPallette));
    smallImage.save(OUTPUT_FOLDER_STR + "/tree_reduced_colors.png");

    if (compareFiles(OUTPUT_FOLDER_STR + "/tree_reduced_colors.png", OUTPUT_FOLDER_STR + "/../tree_reduced_colors.png"))
    {
        virtualPoints++;
    }
    totalPoints += 1;
    PRINT_POINTS;

    P_LOG_INFO() << "--- The color reduction problem END ---\n";
    CHECK_RETURN;
}

int colorProblem()
{
    P_LOG_INFO() << "---Color problem START---\n";
    std::unordered_map<pixelmancy::Color, std::string> colors;

    colors.emplace(pixelmancy::Color(200, 200, 21), "RG_200_B_21");
    colors.emplace(pixelmancy::Color(200, 200, 21), "RG_200_B_21_2");
    colors.emplace(pixelmancy::Color(200, 200, 20), "RG_200_B_20");
    colors.emplace(pixelmancy::Color(200, 200, 20), "RG_200_B_20_2");
    colors.emplace(pixelmancy::Color(200, 100, 31), "R_200_G_100_B_30");
    colors.emplace(pixelmancy::Color(200, 200, 31), "R_200_G_200_B_30");
    colors.emplace(pixelmancy::Color(50, 202, 32), "R_50_G_202_B_30");
    colors.emplace(pixelmancy::Color(51, 202, 32), "R_51_G_202_B_30");
    colors.emplace(pixelmancy::Color(40, 203, 33, 20), "R_40_G_200_B_30_A_20");
    colors.emplace(pixelmancy::Color(40, 203, 33, 30), "R_40_G_200_B_30_A_30");
    colors.insert(std::make_pair(pixelmancy::Color(1, 2, 3, 4), "RGBA_1_2_3_4"));
    colors.insert(std::make_pair(pixelmancy::Color(5, 6, 7, 8), "RGBA_5_6_7_8"));
    colors.insert(std::make_pair(pixelmancy::Color(9, 10, 11, 12), "RGBA_9_10_11_12"));
    colors.insert(std::make_pair(pixelmancy::Color(13, 14, 15, 16), "RGBA_13_14_15_16"));
    colors.insert(std::make_pair(pixelmancy::Color(17, 18, 19, 20), "RGBA_17_18_19_20"));

    P_LOG_INFO() << " Max load factor : " << colors.max_load_factor() << "\n";

    if (colors.size() == 13)
    {
        P_LOG_INFO() << "CORRECT: There are thirteen colours in the map\n";
        virtualPoints++;
    }
    else
    {
        P_LOG_ERROR() << "WRONG : Expect thirteen colours in the map, but found  " << colors.size() << "\n";
    }

    auto it = colors.find(pixelmancy::Color(200, 200, 21));
    if (it != colors.end())
    {
        P_LOG_INFO() << "CORRECT: Found color: " << it->second << "\n";
        virtualPoints++;
    }
    else
    {
        P_LOG_ERROR() << "WRONG: Color not found\n";
    }

    it = colors.find(pixelmancy::Color(21, 21, 200));
    if (it != colors.end())
    {
        P_LOG_ERROR() << "WRONG : Found color: " << it->second << "\n";
    }
    else
    {
        P_LOG_INFO() << "CORRECT : Color not found\n";
        virtualPoints++;
    }

    if (colors.insert(std::make_pair(pixelmancy::Color(200, 200, 21), "RG_200_B_21_2")).second)
    {
        P_LOG_ERROR() << "WRONG : Inserted duplicate color\n";
    }
    else
    {
        P_LOG_INFO() << "CORRECT : Did not insert duplicate color\n";
        virtualPoints++;
    }
    totalPoints += 4;
    P_LOG_INFO() << "Bucket count: " << colors.bucket_count() << "\n";
    P_LOG_INFO() << "Load factor: " << colors.load_factor() << "\n";
    PRINT_POINTS;
    P_LOG_INFO() << "---Color problem END---\n\n";
    CHECK_RETURN;
}

int distanceProblem(std::shared_ptr<pixelmancy::ColorMatcher> colorMatcher)
{
    P_LOG_INFO() << "--- Distance problem START ---\n";

    auto RED = pixelmancy::Color(255, 0, 0);
    const auto& nearestClr = colorMatcher->getNearestColor(RED);
    if (RED == nearestClr)
    {
        P_LOG_INFO() << "CORRECT: Nearest color to RED is RED\n";
        virtualPoints++;
    }
    else
    {
        P_LOG_ERROR() << "WRONG: Nearest color to RED is not RED, but : " << nearestClr.toString() << "\n";
    }

    const auto& nearestToGrayClr = colorMatcher->getNearestColor(pixelmancy::GRAY);
    if (pixelmancy::GRAY == nearestToGrayClr)
    {
        P_LOG_INFO() << "CORRECT: Nearest color to GRAY is GRAY\n";
        virtualPoints++;
    }
    else
    {
        P_LOG_ERROR() << "WRONG: Nearest color to GRAY is not GRAY, but : " << nearestToGrayClr.toString() << "\n";
    }

    auto myClor = pixelmancy::Color(240, 240, 200);
    const auto expectedNearestColor = pixelmancy::Color(255, 228, 196);
    const auto& nearestoMyClr = colorMatcher->getNearestColor(myClor);
    if (expectedNearestColor == nearestoMyClr)
    {
        P_LOG_INFO() << "CORRECT: Nearest color to " << myClor.toString() << " is " << nearestoMyClr.toString() << " near to "
                     << expectedNearestColor.toString() << "\n";
        virtualPoints++;
    }
    else
    {
        P_LOG_ERROR() << "WRONG: Nearest color to " << myClor.toString() << " is not " << expectedNearestColor.toString() << " but " << nearestoMyClr.toString()
                      << "\n";
    }
    totalPoints += 3;
    PRINT_POINTS;
    P_LOG_INFO() << "--- Distance problem END ---\n\n";
    CHECK_RETURN;
}

int imageProblem()
{
    P_LOG_INFO() << "--- The image problem START ---\n";
    std::shared_ptr<pixelmancy::graphics::DrawableObject> dObj =
      std::make_shared<pixelmancy::graphics::SquareObject>(pixelmancy::sizei2d({50, 50}), 0, pixelmancy::RED);

    pixelmancy::Image img(100, 100, pixelmancy::WHITE);
    pixelmancy::Image img2(100, 100, pixelmancy::WHITE);

    std::array<pixelmancy::graphics::Point, 3> positions = {
      pixelmancy::graphics::Point(0, 0), pixelmancy::graphics::Point(24, 26), pixelmancy::graphics::Point(50, 50)};
    std::array<pixelmancy::Image, 3> images = {img, img2, std::move(img2)};

    totalPoints++;
    if (std::size(img2) != 0)
    {
        P_LOG_ERROR() << "WRONG : 'img2' should not have pixels data after move\n";
    }
    else
    {
        P_LOG_INFO() << "CORRECT : 'img2' is reset\n";
        virtualPoints++;
    }

    totalPoints++;
    if (img == images[0])
    {
        P_LOG_INFO() << "CORRECT : 'img' should be same after copy\n";
        virtualPoints++;
    }
    else
    {
        P_LOG_ERROR() << "WRONG : 'img' is different after copy\n";
    }
    PRINT_POINTS;
    P_LOG_INFO() << "--- The image problem END ---\n\n";
    CHECK_RETURN;
}

int threePNGBoxes()
{
    P_LOG_INFO() << "--- The boxes problem START ---\n";
    std::shared_ptr<pixelmancy::graphics::DrawableObject> dObj =
      std::make_shared<pixelmancy::graphics::SquareObject>(pixelmancy::sizei2d({50, 50}), 0, pixelmancy::RED);

    pixelmancy::Image img(100, 100, pixelmancy::WHITE);
    pixelmancy::Image img2(100, 100, pixelmancy::WHITE);

    std::array<pixelmancy::graphics::Point, 3> positions = {
      pixelmancy::graphics::Point(4, 6), pixelmancy::graphics::Point(24, 26), pixelmancy::graphics::Point(44, 46)};

    std::array<pixelmancy::Image, 3> images = {img, img2, std::move(img2)};

    for (std::size_t i = 0; i < 3; i++)
    {
        dObj->setPosition(positions[i]);
        dObj->drawOn(images[i]);
    }

    for (std::size_t i = 0; i < 3; i++)
    {
        images[i].save(fmt::format("{}/three_boxes_frame{}.png", OUTPUT_FOLDER_STR, i + 1));
    }

    for (std::size_t i = 0; i < 3; i++)
    {
        if (compareFiles(OUTPUT_FOLDER_STR + "/three_boxes_frame" + std::to_string(i + 1) + ".png",
                         OUTPUT_FOLDER_STR + "/../three_boxes_frame" + std::to_string(i + 1) + ".png"))
        {
            virtualPoints++;
        }
        totalPoints += 1;
    }
    PRINT_POINTS;
    P_LOG_INFO() << "--- The boxes problem END ---\n\n";
    CHECK_RETURN;
}

int threeBoxes(std::shared_ptr<pixelmancy::ColorMatcher> colorMatcher)
{
    P_LOG_INFO() << "--- The boxes GIF problem START ---\n";
    totalPoints += 2;
    {
        pixelmancy::Gif gif(colorMatcher);
        std::vector<std::unique_ptr<pixelmancy::graphics::DrawableObject>> dObjs;
        dObjs.push_back(std::make_unique<pixelmancy::graphics::SquareObject>(pixelmancy::sizei2d({50, 50}), 0, pixelmancy::RED));
        dObjs.push_back(std::make_unique<pixelmancy::graphics::CircleObject>(15, 2, pixelmancy::LIGHT_GOLDEN_ROD_YELLOW, pixelmancy::DARK_GOLDEN_ROD));
        std::array<pixelmancy::graphics::Point, 3> positions = {
          pixelmancy::graphics::Point(0, 0), pixelmancy::graphics::Point(24, 26), pixelmancy::graphics::Point(50, 50)};

        for (std::size_t i = 0; i < 3; i++)
        {
            int offset = 0;
            pixelmancy::Image img(100, 100, pixelmancy::WHITE);
            for (auto& dObj : dObjs)
            {
                auto pos = positions[i];
                // move circle to the middle of the square
                if (dObj->getObjectType() == pixelmancy::graphics::ObjectType::CIRCLE)
                {
                    pos = pos + pixelmancy::graphics::Point(25, 25);
                }
                dObj->setPosition(pos);
                dObj->drawOn(img);
                offset++;
            }
            gif.addFrame(img);
        }
        if (gif.save(OUTPUT_FOLDER_STR + "/three_boxes.gif"))
        {
            P_LOG_INFO() << "CORRECT: GIF saved successfully\n";
            virtualPoints += 1;
        }
        else
        {
            P_LOG_ERROR() << "WRONG: GIF not saved\n";
        }
        gif.close();
    }

    if (compareFiles(OUTPUT_FOLDER_STR + "/three_boxes.gif", OUTPUT_FOLDER_STR + "/../three_boxes.gif"))
    {
        virtualPoints += 1;
    }
    PRINT_POINTS;
    P_LOG_INFO() << "--- The boxes GIF problem END ---\n\n";
    CHECK_RETURN;
}

int drawOnImage(std::shared_ptr<pixelmancy::ColorMatcher> colorMatcher)
{
    P_LOG_INFO() << "--- The draw on image problem START ---\n";

    pixelmancy::Gif gif(colorMatcher);
    pixelmancy::graphics::SquareObject rec({2, 2}, 0, pixelmancy::SNOW);
    auto img = pixelmancy::Image::loadFromFile(TREE_IMAGE);
    pixelmancy::Image smallImage = img.resize(0.5);
    smallImage.blueShift();
    smallImage.removeAlphaChannel();
    smallImage.reduceColorPalette(64);
    smallImage.save(OUTPUT_FOLDER_STR + "/small_tree.png");

    P_LOG_INFO() << fmt::format("smallImage size : {}x{} wxh\n", smallImage.getWidth(), smallImage.getHeight());

    std::vector<pixelmancy::graphics::Point> positions(70);
    for (int j = 0; j < 70; j++)
    {
        int x = rand() % smallImage.getWidth();
        int y = rand() % smallImage.getHeight();
        positions.push_back({x, y});
    }

    auto loopBack = [](int pos, int max) { return (pos >= max) ? pos % max : pos; };

    auto colorPallette = smallImage.getColorPalette();
    P_LOG_INFO() << fmt::format("Color pallette szie : {}\n", colorPallette.size());

    pixelmancy::Image imgCopy2(smallImage);
    const int frameDelay = 9;
    for (int i = 0; i < 25; i++)
    {
        pixelmancy::Image imgCopy(smallImage);
        for (const auto& [x, y] : positions)
        {
            int xPos = loopBack(x + i * 2, imgCopy.getWidth());
            int yPos = loopBack(y + i, imgCopy.getHeight());
            rec.setPosition({xPos, yPos});
            rec.drawOn(imgCopy);
        }
        gif.addFrame(imgCopy, frameDelay);
    }
    colorPallette.swapColor(pixelmancy::Color(28, 176, 176), pixelmancy::ROSY_BROWN);
    for (int i = 25; i < 50; i++)
    {
        pixelmancy::Image imgCopy(smallImage);
        imgCopy.replaceColorPalette(colorPallette);
        for (const auto& [x, y] : positions)
        {
            int xPos = loopBack(x + i * 2, imgCopy.getWidth());
            int yPos = loopBack(y + i, imgCopy.getHeight());
            rec.setPosition({xPos, yPos});
            rec.drawOn(imgCopy);
        }
        gif.addFrame(imgCopy, frameDelay);
    }
    colorPallette.swapColor(pixelmancy::Color(16, 72, 72), pixelmancy::BROWN);
    for (int i = 50; i < 75; i++)
    {
        pixelmancy::Image imgCopy(smallImage);
        imgCopy.replaceColorPalette(colorPallette);
        for (const auto& [x, y] : positions)
        {
            int xPos = loopBack(x + i * 2, imgCopy.getWidth());
            int yPos = loopBack(y + i, imgCopy.getHeight());
            rec.setPosition({xPos, yPos});
            rec.drawOn(imgCopy);
        }
        gif.addFrame(imgCopy, frameDelay);
    }
    colorPallette.swapColor(pixelmancy::Color(24, 112, 112), pixelmancy::OLIVE);
    for (int i = 75; i < 100; i++)
    {
        pixelmancy::Image imgCopy(smallImage);
        imgCopy.replaceColorPalette(colorPallette);
        for (const auto& [x, y] : positions)
        {
            int xPos = loopBack(x + i * 2, imgCopy.getWidth());
            int yPos = loopBack(y + i, imgCopy.getHeight());
            rec.setPosition({xPos, yPos});
            rec.drawOn(imgCopy);
        }
        gif.addFrame(imgCopy, frameDelay);
    }
    gif.save(OUTPUT_FOLDER_STR + "/draw_on_tree.gif");
    gif.close();
    if (fakeCompareFiles(OUTPUT_FOLDER_STR + "/draw_on_tree.gif", OUTPUT_FOLDER_STR + "/../draw_on_tree.gif"))
    {
        virtualPoints += 1;
    }
    totalPoints += 1;
    PRINT_POINTS;
    P_LOG_INFO() << "--- The draw on image problem END ---\n";
    CHECK_RETURN;
}

int circleRotating(std::shared_ptr<pixelmancy::ColorMatcher> colorMatcher)
{
    P_LOG_INFO() << "--- The rotating circles problem START ---\n";
    pixelmancy::Gif gif(colorMatcher);
    auto circle = pixelmancy::graphics::CircleObject(10, 2, pixelmancy::MAGENTA, pixelmancy::GREEN);
    const int frames = 2;
    for (int i = 0; i < frames; i++)
    {
        pixelmancy::Image img(550, 550);
        pixelmancy::sizei2d center = {275, 275};
        int radius = 240;
        const double frameTheta = i * 5 * M_PI / 180;
        for (int j = 0; j < 360; j += 10)
        {
            double theta = frameTheta + j * M_PI / 180;
            int x = center.width + radius * cos(theta);
            int y = center.height + radius * sin(theta);
            circle.setPosition({x, y});
            circle.drawOn(img);
        }
        gif.addFrame(img);
    }
    gif.save(OUTPUT_FOLDER_STR + "/circle_rotating.gif");
    gif.close();
    PRINT_POINTS;
    P_LOG_INFO() << "--- The rotating circles problem END ---\n";
    CHECK_RETURN;
}

int wheel(std::shared_ptr<pixelmancy::ColorMatcher> colorMatcher)
{
    P_LOG_INFO() << "--- The wheel problem START ---\n";
    pixelmancy::Gif gif(colorMatcher);
    auto circle = pixelmancy::graphics::CircleObject(10, 2, pixelmancy::MAGENTA, pixelmancy::GREEN);
    auto circleType2 = pixelmancy::graphics::CircleObject(6, 2, pixelmancy::YELLOW, pixelmancy::VIOLET);
    auto circleMiddle = pixelmancy::graphics::CircleObject(80, 2, pixelmancy::YELLOW_GREEN, pixelmancy::RED);
    auto circleMiddle2 = pixelmancy::graphics::CircleObject(63, 2, pixelmancy::BLANCHED_ALMOND, pixelmancy::RED);
    auto circleMiddle3 = pixelmancy::graphics::CircleObject(60, 2, pixelmancy::BLACK, pixelmancy::RED);
    pixelmancy::graphics::SquareObject rec({10, 235}, 0, pixelmancy::WHITE);
    const int frames = 2;
    const pixelmancy::graphics::Point middlePos = {275, 275};
    circleMiddle.setPosition(middlePos);
    circleMiddle2.setPosition(middlePos);
    circleMiddle3.setPosition(middlePos);
    rec.setPosition({275, 275});

    for (int i = 0; i < frames; i++)
    {
        pixelmancy::Image img(550, 550);
        pixelmancy::sizei2d center = {275, 275};
        const int radius = 240;
        const double frameTheta = i * 5 * M_PI / 180;
        for (int j = 0; j < 360; j += 10)
        {
            double theta = frameTheta + j * M_PI / 180;
            int x = static_cast<int>(center.width + radius * cos(theta));
            int y = static_cast<int>(center.height + radius * sin(theta));
            const int colorSelect = ((j > 20 ? j % 20 : j) + 90) / 10;
            circle.setFillColor(colorSelect % 2 ? pixelmancy::MAGENTA : pixelmancy::ORANGE);
            circle.setPosition({x, y});
            circle.drawOn(img);
            rec.setFillColor(pixelmancy::FULL_PALLETTE[colorSelect]);
            rec.setAngle(j + 11 + i * 5);
            rec.drawOn(img);
        }
        circleMiddle.drawOn(img);
        circleMiddle2.drawOn(img);
        circleMiddle3.drawOn(img);
        int radius2 = 70;
        for (int j = 0; j < 360; j += 10)
        {
            double theta = frameTheta + j * M_PI / 180;
            int x2 = static_cast<int>(center.width + radius2 * cos(theta));
            int y2 = static_cast<int>(center.height + radius2 * sin(theta));
            circleType2.setPosition({x2, y2});
            circleType2.drawOn(img);
        }
        gif.addFrame(img);
    }
    gif.save(OUTPUT_FOLDER_STR + "/wheel.gif");
    gif.close();
    PRINT_POINTS;
    P_LOG_INFO() << "--- The rotating circles problem END ---\n";
    CHECK_RETURN;
}

int main(int argc, char* argv[])
{
    pixelmancy::logger::Log::Init(pixelmancy::logger::LogLevel::WARN);
    std::shared_ptr<pixelmancy::ColorMatcher> colorMatcher = std::make_shared<pixelmancy::ColorMatcher>();

    cxxopts::Options options("Pixelmancy", "A simple GIF library");

    options.add_options()
        ("h,help", "Print help")
        ("c,color", "Color problem")
        ("d,distance", "Distance problem")
        ("i,image", "Image problem")
        ("p,three-png-boxes", "Three PNG boxes problem")
        ("t,three-boxes", "Three boxes problem")
        ("r,image-resize", "Image resize problem")
        ("g,draw-on-image", "Draw on image problem")
        ("o,circle-rotating", "Circle rotating problem")
        ("w,wheel", "Wheel problem");

    auto result = options.parse(argc, argv);
    if (result.count("help") == 1)
    {
        std::cout << options.help() << std::endl;
        exit(1);
    }

    if (result["color"].as<bool>())
    {
        return colorProblem();
    }

    if (result["distance"].as<bool>())
    {
        return distanceProblem(colorMatcher);
    }

    if (result["image"].as<bool>())
    {
        return imageProblem();
    }

    if (result["three-png-boxes"].as<bool>())
    {
        return threePNGBoxes();
    }

    if (result["three-boxes"].as<bool>())
    {
        return threeBoxes(colorMatcher);
    }

    if (result["image-resize"].as<bool>())
    {
        return imageResize();
    }

    if (result["draw-on-image"].as<bool>())
    {
        return drawOnImage(colorMatcher);
    }

    if (result["wheel"].as<bool>())
    {
        return wheel(colorMatcher);
    }

    if (result["circle-rotating"].as<bool>())
    {
        return circleRotating(colorMatcher);
    }
    return 0;
}
