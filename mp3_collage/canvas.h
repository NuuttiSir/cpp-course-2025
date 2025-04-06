/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "drawable.h"
#include "pnglayer.h"
#include <memory>
#include <vector>

class Canvas : public Drawable {
public:
  Canvas();
  ~Canvas();
  void Add(size_t x, size_t y, const Vector2 &pos, const Vector2 &scale,
           const RGBAPixel &col, const std::string &name);
  PNGLayer &GetTopLayer();
  PNGLayer &GetByName(const std::string &name);
  void Remove(const std::string &name);
  void Swap(const std::string &name1, const std::string &name2);
  void draw(PNG &canvas) const;

private:
  std::vector<std::unique_ptr<PNGLayer>> layers;
  size_t layercount = 0;
};

#endif
