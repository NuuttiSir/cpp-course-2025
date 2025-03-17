#include "RGBA/png.h"
#include "RGBA/rgbapixel.h"

#include <cstdio>
#include <string>
#include <cmath>

void rotate(const std::string & inputFile, const std::string & outputFile) {
	PNG pic(inputFile);
	PNG rotatedPic(pic.height(), pic.width());

	size_t height = pic.height();
	size_t width = pic.width();

	for (size_t i = 0; i < width; i++) {
		for (size_t j = 0; j < height; j++) {
			RGBAPixel& pixel = pic(i, j);
			RGBAPixel& newPixel = rotatedPic(j, width - i - 1);
			newPixel = pixel;
		}
	}
	
	rotatedPic.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			RGBAPixel& pixel = png(i, j);
			pixel.red = (i * j) % 256;
			pixel.green = (i - j) % 256;
			pixel.blue = (i + j) % 256;
		}
	}

	return png;
}
