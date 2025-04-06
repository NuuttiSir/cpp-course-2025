/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include <iostream>
#include <memory>

#include "png.h"
#include "color.h"
#include "shape.h"
#include "triangle.h"
#include "vector2.h"

int main()
{
	const int canvas_width = 128;
	const int canvas_height = 128;

	PNG canvas;
	canvas.resize(canvas_width, canvas_height);


	const RGBAPixel triangle_color = color::ORANGE;
	std::unique_ptr<Shape> triangle = std::make_unique<Triangle>(triangle_color,
			Vector2(32, 32),
			Vector2(64, 64),
			Vector2(32, 64));

	triangle->draw(canvas);

	canvas.writeToFile("test_destructor.png");

	/* TODO: Why is this leaking memory?  Triangle does have a valid destructor!?
	 * Can you stop it from leaking WITHOUT changing triangle's type from a
	 * Shape pointer to a Triangle pointer type? */

	return 0;
}
