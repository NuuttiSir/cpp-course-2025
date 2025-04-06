/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include <iostream>
#include <memory>

#include "truck.h"

int main()
{
	PNG canvas;
	canvas.resize(128, 128);

	const Vector2 truck_center(64, 64);

	/* TODO: Why can't I construct a new Truck?  Is should be a valid Drawable.
	 * Could it be missing something that would prevent it from being constructed?
	 */
	std::unique_ptr<Drawable> truck = std::make_unique<Truck>(truck_center);

	truck->draw(canvas);

	canvas.writeToFile("test_pure_virtual.png");

	return 0;
}
