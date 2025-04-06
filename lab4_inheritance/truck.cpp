/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 *
 * Please see truck.h for documentation of the Truck class
 */

#include "truck.h"

#include "color.h"

const int TRAILER_WIDTH = 48;
const int TRAILER_HEIGHT = 16;
const RGBAPixel TRAILER_COLOR = color::BLUE;

const int CABIN_WIDTH = 8;
const int CABIN_HEIGHT = 12;
const RGBAPixel CABIN_COLOR = color::RED;

const int ENGINE_WIDTH = 6;
const int ENGINE_HEIGHT = 8;
const RGBAPixel ENGINE_COLOR = color::RED;

const int WINDOW_WIDTH = 4;
const int WINDOW_HEIGHT = 4;
const RGBAPixel WINDOW_COLOR = color::BLUE;

const int WHEEL_RADIUS = 3;
const RGBAPixel WHEEL_COLOR = color::BLACK;

const int NUM_WHEELS = 5;


Truck::Truck(const Vector2& pcenter)
	: center_(pcenter),
	trailer(Vector2(center_.x()-TRAILER_WIDTH/2, center_.y()), TRAILER_COLOR, TRAILER_WIDTH, TRAILER_HEIGHT),
	cabin(Vector2(center_.x()+CABIN_WIDTH/2,
					(center_.y()+TRAILER_HEIGHT/2)-CABIN_HEIGHT/2), CABIN_COLOR, CABIN_WIDTH, CABIN_HEIGHT),
	window(Vector2(cabin.center().x(),
					cabin.center().y()-WINDOW_HEIGHT/2), WINDOW_COLOR, WINDOW_WIDTH,
				WINDOW_HEIGHT),
	engine(Vector2(cabin.center().x()+CABIN_WIDTH/2 +
					ENGINE_WIDTH/2,
					(cabin.center().y()+CABIN_HEIGHT/2) - ENGINE_HEIGHT/2), ENGINE_COLOR,
				ENGINE_WIDTH, ENGINE_HEIGHT)
{
	const int left = (static_cast<int>(trailer.center().x()) - trailer.width() / 2) +
		WHEEL_RADIUS;
	const int right = (static_cast<int>(trailer.center().x()) + trailer.width() / 2) -
		WHEEL_RADIUS;
	const int y = (WHEEL_RADIUS*1/2 + static_cast<int>(trailer.center().y()) +
			trailer.height() / 2);
	wheels.emplace_back(Vector2(left, y), WHEEL_COLOR, WHEEL_RADIUS);
	wheels.emplace_back(Vector2(left+WHEEL_RADIUS*2, y), WHEEL_COLOR, WHEEL_RADIUS);
	wheels.emplace_back(Vector2(right, y), WHEEL_COLOR, WHEEL_RADIUS);
	wheels.emplace_back(Vector2(right-WHEEL_RADIUS*2, y), WHEEL_COLOR, WHEEL_RADIUS);
	wheels.emplace_back(Vector2(engine.center().x()-WHEEL_RADIUS, y), WHEEL_COLOR, WHEEL_RADIUS);
}

Truck::Truck(const Truck& other)
	: center_(other.center_),
	wheels(other.wheels),
	trailer(other.trailer),
	cabin(other.cabin),
	window(other.window),
	engine(other.engine)
{

}

Truck::~Truck()
{
	clear();  
}

Truck& Truck::operator=(const Truck& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	clear();
	copy(rhs);
	return *this;
}

Vector2 Truck::center() const
{
	return this->center_;
}

void Truck::set_center(const Vector2& pcenter)
{
	const Vector2 delta(this->center_ - pcenter);
	this->center_ = this->center_ + delta;
	for (int i = 0; i < NUM_WHEELS; i++)
	{
		wheels[i].set_center(wheels[i].center() + delta);
	}
	trailer.set_center(trailer.center() + delta);
	cabin.set_center(cabin.center() + delta);
	window.set_center(window.center() + delta);
	engine.set_center(engine.center() + delta);
}

void Truck::copy(const Truck& other)
{
	center_ = other.center_;
	wheels = other.wheels;
	trailer = other.trailer;
	cabin = other.cabin;
	window = other.window;
	engine = other.engine;
}

void Truck::clear()
{
  // Nothing to do here as we do not have raw pointers to worry about
}



