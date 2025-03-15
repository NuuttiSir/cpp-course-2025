/**
 * @file rgbapixel.cpp
 * Implementation of the RGBAPixel class for the EasyPNG library.
 *
 * @author Chase Geigle
 * @author Anna LaValle
 * @date Created: Spring 2012
 * @date Modified: Spring 2025
 */
#include "rgbapixel.h"
#include <cstdint>

// Your code here
RGBAPixel::RGBAPixel() {
    red = 255;
    green = 255;
    blue = 255;
    alpha = 255;
}

RGBAPixel::RGBAPixel(uint8_t _r, uint8_t _g, uint8_t _b) {
    red = _r;
    green = _g;
    blue = _b;
    alpha = 255;
}
