
#include <iostream>
#include <memory>
#include "png.h"

std::unique_ptr<PNG> colorize(std::unique_ptr<PNG> original);
std::unique_ptr<PNG> addBorders(std::unique_ptr<PNG> original);
std::unique_ptr<PNG> sketchify(std::unique_ptr<PNG> original);
void processImage();

int main()
{
     try {
           processImage();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

           
}
