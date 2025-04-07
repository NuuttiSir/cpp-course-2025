/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include "canvas.h"
#include <iostream>

Canvas::Canvas()
{
  layers.reserve(10); 
  layercount = 0;
}

// Just delete the list, the individual layers are handled by main
Canvas::~Canvas()
{
  layercount = 0;
}

// Add an layer at the end of the list
void Canvas::Add(size_t x, size_t y, const Vector2& pos, const Vector2& scale, const RGBAPixel& col, const std::string& name)
{
	layers.emplace_back(x,y,pos,scale,col,name);
	layercount++;
}

// Add an layer at the end of the list
void Canvas::Add(PNGLayer const & layer)
{
	layers.emplace_back(layer);
	layercount++;
}

PNGLayer & Canvas::GetTopLayer(){

	return layers.back();
}

// Get an layer by its name
// Return as pointer to allow editing or drawing on it
PNGLayer& Canvas::GetByName(const std::string& name){
  	for(auto& layer : layers){
		if(layer.getName()==name)
			return layer;
	}

	throw std::runtime_error("Layer not found" + name);
	
}

// Find and remove layer by name
// If layer is not found, do nothing
void Canvas::Remove(const std::string& name)
{
	for(auto it=layers.begin(); it!=layers.end(); it++){
	  if((*it).getName()==name){
			layers.erase(it);
			layercount--;
			return;
	  }
	}

}

// Find given layers from list and swap their positions
// Swap only if both layers are found
void Canvas::Swap(const std::string& name1, const std::string& name2)
{
  	int index1 = -1; int index2 = -1;
	for(size_t i=0;i<layers.size();i++){
		if(layers[i].getName()==name1)
			index1 = i;
		if(layers[i].getName()==name2)
			index2 = i;
		if(index1>=0 && index2>=0){
			std::swap(layers[index1],layers[index2]);
			return;
		}
	}
}

// Draws all layers in the list in order
// Blends the pixels colors of the layers with their layer color
// Draws the layers in their given position and scales them accordingly
// Blends drawn layers based on alpha channel (transparency)
void Canvas::draw(PNG& canvas) const
{
	for(size_t i=0; i<layercount; i++) {
	  const PNGLayer& layer = layers[i];
		
		for(size_t x=0, xmax = layer.width(); x<xmax; x++){
			for(size_t y=0, ymax = layer.height(); y<ymax; y++){
				// This gets the pixel color blended with layer color
				// Check pnglayer.cpp
				RGBAPixel coli = layer.getBlendedPixel(x,y);
				Vector2 sc = layer.getScale();
				
				// You should uncomment the below line and use in the section below
				Vector2 pos = layer.getPosition();
				
				// A loop is needed in case it must be scaled up, or we end up with gaps
				for(int xs=0; xs < std::abs((int)(sc.x()-0.001))+1; xs++){
					for(int ys=0; ys < std::abs((int)(sc.y()-0.001))+1; ys++){
						// Determine the position on the canvas based on 
						// layer position, scale, pixel position and adjacent pixel selection
						int x1 = pos.x() + x * sc.x() + xs;
						int y1 = pos.y() + y * sc.y() + ys;
			
						// Check that it's within bounds
						if(x1 >= 0 && x1 < (int)canvas.width() && y1 >= 0 && y1 < (int)canvas.height()) {
							// Current color of the canvas
							RGBAPixel& colc = canvas(x1,y1);
														
							// Blend based on alpha.
							// Multiply layer color with alpha, canvas color with 255-alpha
							// Add them and divide by 255
							// In other words 255 = replace old pixel with new. 0 = don't draw.
							// 1-254 = partly new pixel, partly old
							
							colc.red = ((255-coli.alpha) * colc.red + coli.alpha * coli.red) / 255;
							colc.green = ((255-coli.alpha) * colc.green + coli.alpha * coli.green) / 255;
							colc.blue = ((255-coli.alpha) * colc.blue + coli.alpha * coli.blue) / 255;

							// We can keep the canvas opaque, no reason to change it
							colc.alpha = 255;
						}
					}
				}
			}
		}
	}
}
