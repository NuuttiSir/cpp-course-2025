/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include "png.h"
#include "color.h"
#include "rectangle.h"
#include "shape.h"
#include "vector2.h"
#include "line.h"
#include "triangle.h"
#include <memory>
#include <vector>

const char OUTPUT_FILE[] = "out.png";
const int WIDTH = 128;
const int HEIGHT = 128;
const Vector2 CENTER(WIDTH / 2, HEIGHT / 2);


int main()
{
	const int s_width = 16;
	const int s_height = 16;
	Vector2 s_center(32, 16);
	std::vector<std::unique_ptr<Drawable>> drawables;
	// I can add a Rectangle to a vector of Drawables!
	drawables.push_back(std::make_unique<Rectangle>(s_center,
			color::RED,
			s_width,
			s_height));

	// I can add a cross Shape to a vector of Drawables!
	drawables.push_back(std::make_unique<Shape>(s_center+Vector2(4*s_width/2,s_height/2),color::ORANGE));

	// I can add a Line  to a vector of Drawables!
	drawables.push_back(std::make_unique<Line>(s_center + Vector2(5*s_width/2,0), 
			s_center+Vector2(s_width,0),
			color::BLACK));

	PNG canvas;
	canvas.resize(WIDTH, HEIGHT);

	// Since they are all drawable I can call draw on all of them
	for (size_t i = 0; i < drawables.size(); i++)
	{
		drawables[i]->draw(canvas);
	}

	canvas.writeToFile(OUTPUT_FILE);

	return 0;
}
