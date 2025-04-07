/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#ifndef CANVASITEM_H
#define CANVASITEM_H

#include <string>
#include "png.h"
#include "vector2.h"
#include "rgbapixel.h"

class PNGLayer : public PNG
{
	public:
		// x and y here represent size in pixels
		PNGLayer(size_t x, size_t y, const Vector2& pos, const Vector2& scale, const RGBAPixel& col, const std::string& name);
		PNGLayer() {}
		const Vector2& getPosition() const;
		const Vector2& getScale() const;
		const std::string& getName() const;
		RGBAPixel getBlendedPixel(size_t x, size_t y) const;
		void SetPosition(const Vector2& pos);
	private:
		Vector2 position_;
		Vector2 scale_;
		RGBAPixel color_;
		std::string name_;
};

#endif

