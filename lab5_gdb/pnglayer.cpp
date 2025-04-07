/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include "pnglayer.h"

PNGLayer::PNGLayer(size_t x, size_t y, const Vector2& position, const Vector2& scale, const RGBAPixel& color, const std::string& name) 
						: position_(position), scale_(scale), color_(color), name_(name) {
	resize(x, y);
	for (size_t i = 0; i < x; i++) {
		for (size_t j = 0; j < y; j++) {
			RGBAPixel& pixel = (*this)(i,j);
			pixel.red = 255;
			pixel.green = 255;
			pixel.blue = 255;
			pixel.alpha = 0;  // Set alpha to 0 to make the pixel fully transparent
		}
	}
}

RGBAPixel PNGLayer::getBlendedPixel(size_t x, size_t y) const{
	RGBAPixel copy = (*this)(x,y);

	// Blend the pixel with color_
	// Multiply the colors per channel and divide by 255
	// Result should be stored in a copy so we don't modify the original PNG
	// This way the color can be easily changed later
	copy.red = copy.red * color_.red / 255;
	copy.green = copy.green * color_.green / 255;
	copy.blue = copy.blue * color_.blue / 255;
	copy.alpha = copy.alpha * color_.alpha / 255;

	return copy;
}

const Vector2& PNGLayer::getPosition() const{
	return position_;
}

const Vector2& PNGLayer::getScale() const{
	return scale_;
}

const std::string& PNGLayer::getName() const{
	return name_;
}


void PNGLayer::SetPosition(const Vector2& pos){
	position_ = pos;
}
