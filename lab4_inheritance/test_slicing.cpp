/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include <iostream>
#include <memory>

#include "png.h"
#include "flower.h"

int main()
{
	const int canvas_width = 128;
	const int canvas_height = 128;

	PNG canvas;
	canvas.resize(canvas_width, canvas_height);

	const Vector2 flower_center(canvas_width/2, canvas_height/2);

	auto flower = std::make_unique<Flower>(flower_center);

	/* TODO: For some reason this flower is not drawing correctly?  The stem,
	 * pistil, and leaf are all being drawn as big giant X's. */
	flower->draw(canvas);

	canvas.writeToFile("test_slicing.png");

	return 0;
}
