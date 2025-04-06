/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
*/

#ifndef FLOWER_H_
#define FLOWER_H_

#include "shape.h"

class Flower : public Drawable
{
	private:
		Shape stem;
		Shape pistil;  // center piece of flower
		Shape leaf;

		void drawPedals(PNG& canvas, const Vector2& center, int x, int y) const;
	public:
		Flower(const Vector2& center);
		void draw(PNG& canvas) const;
};

#endif  // FLOWER_H_
