#include "RGBA/png.h"
#include "RGBA/rgbapixel.h"

#include <string>
#include <cmath>

void rotate(const std::string & inputFile, const std::string & outputFile) {
	PNG pic(inputFile);
	// Your code here
	
	
	rotatedPic.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	// Your code here

	return png;
}
