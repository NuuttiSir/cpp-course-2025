/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include <iostream>
#include <memory>

#include "color.h"
#include "rectangle.h"
#include "vector2.h"

int main()
{
	const int canvas_width = 128;
	const int canvas_height = 128;

	PNG canvas;
	canvas.resize(canvas_width, canvas_height);

	Vector2 rectangle_center(canvas_width / 2, canvas_height / 2);
	const int rectangle_width = canvas_width / 4;
	const int rectangle_height = canvas_height / 4;
	std::shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>(rectangle_center,
			color::BLUE,
			rectangle_width,
			rectangle_height);

	rectangle->draw(canvas);

	const int rectangle_perimeter = rectangle->perimeter();
	std::cout << "Rectangle's Perimeter = " << rectangle_perimeter << std::endl;
	const int rectangle_area = rectangle->area();
	std::cout << "Rectangle's Area = " << rectangle_area << std::endl;

	/* But we can treat a Rectangle just like a Shape using a Shape pointer */
	std::shared_ptr<Shape> shape = rectangle;
	const int shape_perimeter = shape->perimeter();
	std::cout << "Shape's Perimeter = " << shape_perimeter << std::endl;
	const int shape_area = shape->area();
	std::cout << "Shape' Area = " << shape_area << std::endl;

	/* TODO: For some reason the shape's area and perimeter is different from
	 * triangle's area and perimeter even though they are pointing to the same
	 * object!  Can you this this so they are the same WITHOUT changing the
	 * shape's type from a Shape pointer to a Triangle pointer? */
	if (rectangle_perimeter == shape_perimeter)
	{
		std::cout << "The Perimeters are the same!" << std::endl;
	} else
	{
		std::cout << "The Perimeters are NOT the same." << std::endl;
	}

	if (rectangle_area == shape_area)
	{
		std::cout << "The Areas are the same!" << std::endl;
	} else
	{
		std::cout << "The Areas are NOT the same." << std::endl;
	}

	canvas.writeToFile("test_virtual.png");

	return 0;
}
