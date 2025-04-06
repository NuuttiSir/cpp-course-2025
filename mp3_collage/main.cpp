/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include <vector>
#include <memory>
#include "png.h"
#include "color.h"
#include "line.h"
#include "triangle.h"
#include "rectangle.h"
#include "shape.h"
#include "vector2.h"
#include "canvas.h"
#include "pnglayer.h"

void AssembleOutPNG()
{
	const std::string OUTPUT_FILE = "out.png";
	const int WIDTH = 128;
	const int HEIGHT = 128;
	
	// Let's define drawables, canvas png layers and the output canvas
	std::vector<std::unique_ptr<Drawable>> drawables;
	Canvas outputCanvas;
	
	// Define a white + shape in quarter of the size of the output canvas
	// We want to draw them white so we can define the color with png layer color
	drawables.push_back(std::make_unique<Line>(Vector2(0.5*WIDTH/4, 0.0), Vector2(0.5*WIDTH/4, 1.0*HEIGHT/4), RGBAPixel(255,255,255)));
	drawables.push_back(std::make_unique<Line>(Vector2(0.0, 0.5*HEIGHT/4), Vector2(1.0*WIDTH/4, 0.5*HEIGHT/4), RGBAPixel(255,255,255)));
	
	// Define a white triangle
	drawables.push_back(std::make_unique<Triangle>(RGBAPixel(255,255,255), Vector2(0.0, 0.0), Vector2(WIDTH, HEIGHT/2), Vector2(0.0, HEIGHT)));

	// Some text in the background, should be partly obscured by the + shapes
	// Since this is added to the canvas first, it will be drawn first
	outputCanvas.Add(WIDTH, HEIGHT, Vector2(0.0, 0.0), Vector2(1.0, 1.0), RGBAPixel(0,0,255), "background");
	outputCanvas.GetTopLayer().readFromFile("Images/background.png");

	// These png layers should match the size of the drawables
	// They are then scaled up which should make them look thicker
	// We also position them in the corners and give them distinct color
	// Draw the + shapes to their intended png layers
	for (size_t i=0; i<2; i++) {
		outputCanvas.Add(WIDTH/4, HEIGHT/4, Vector2(i*WIDTH/2, 0), Vector2(2.0, 2.0), 
						RGBAPixel(i == 0 ? 255 : 0, i == 1 ? 255 : 0, 0, 127), "plus"+std::to_string(i));
		drawables[0]->draw(outputCanvas.GetTopLayer());
		drawables[1]->draw(outputCanvas.GetTopLayer());
	}
	
	// Define the png layers for the triangles then draw them
	// Draw the triangles to their intended png layers in the output canvas
	for (size_t i=3; i<5; i++) {
		outputCanvas.Add(WIDTH, HEIGHT, Vector2(WIDTH/2, HEIGHT/2), 
				Vector2(i==3 ? -0.5 : 0.5, 0.5), RGBAPixel(0, i == 3 ? 255 : 0, i == 4 ? 255 : 0), "triangle"+std::to_string(i));
		drawables[2]->draw(outputCanvas.GetTopLayer());
	}
	
	// Big + in the middle
	outputCanvas.Add(WIDTH, HEIGHT, Vector2(-3.0, -3.0), Vector2(4.1, 4.1), RGBAPixel(0,0,0,255),"bigplus");
	
	drawables[0]->draw(outputCanvas.GetTopLayer());
	drawables[1]->draw(outputCanvas.GetTopLayer());
	
	// Some text in the foreground, should partly obscure the + shapes
	outputCanvas.Add(WIDTH, HEIGHT, Vector2(0.0, 0.0), Vector2(1.0, 1.0), RGBAPixel(255,0,0,127), "foreground");
	outputCanvas.GetTopLayer().readFromFile("Images/foreground.png");

	// The order of png layers on the canvas is important!
	
	// This is our final output. The output canvas draws all its layers in order, blending based on alpha channel
	PNG out(WIDTH, HEIGHT);
	outputCanvas.draw(out);
	out.writeToFile(OUTPUT_FILE);
}

void AssembleCollagePNG(){
	const std::string OUTPUT_FILE = "collage.png";
	std::string INPUT_FILE = "Images/1.png";
	// Line thickness
	const int th = 8;
	
	// Let's define canvas png layers and the output canvas
	Canvas outputCanvas;

	PNG out("Images/5.png");
	int WIDTH = out.width();
	int HEIGHT = out.height();
	
	// Load our images for the collage
	for (size_t i=0; i<4; i++){
		// Converting number to ASCII number characters
		INPUT_FILE[7] = (char)(i+49);
		outputCanvas.Add(WIDTH, HEIGHT, Vector2(0.0, 0.0), Vector2(1.0, 1.0), i==0 ? RGBAPixel(255,0,196) : RGBAPixel(255,255,255,255),"image"+std::to_string(i+1));
		outputCanvas.GetTopLayer().readFromFile(INPUT_FILE);
	}
	
	// Define canvas png layers for frames, matching the size of the respective images
	for (size_t i=4; i<8; i++) {
		PNGLayer& img = outputCanvas.GetByName("image"+std::to_string(i-3));
		Vector2 framesize(img.width()+th*2, img.height()+th*2);
		outputCanvas.Add(framesize.x(), framesize.y(), Vector2(0.0, 0.0), Vector2(1.0, 1.0), RGBAPixel(50,0,200),"frame"+std::to_string(i-3));
		Rectangle rec(framesize/2, RGBAPixel(255,255,255), framesize.x(), framesize.y());
		rec.draw(outputCanvas.GetTopLayer());
	}
	
	// Arrange them somehow
	outputCanvas.GetByName("image1").SetPosition(Vector2(1800.0, 50.0));
	outputCanvas.GetByName("frame1").SetPosition(Vector2(1800.0-th, 50.0-th));
	outputCanvas.GetByName("image2").SetPosition(Vector2(200.0, 700.0));
	outputCanvas.GetByName("frame2").SetPosition(Vector2(200.0-th, 700.0-th));
	outputCanvas.GetByName("image3").SetPosition(Vector2(1300.0, 700.0));
	outputCanvas.GetByName("frame3").SetPosition(Vector2(1300.0-th, 700.0-th));
	outputCanvas.GetByName("image4").SetPosition(Vector2(650.0, 50.0));
	outputCanvas.GetByName("frame4").SetPosition(Vector2(650.0-th, 50.0-th));
	
	// We should put the frames under the images so it only shows up on the sides
	for(size_t i=1; i<5; i++){
		outputCanvas.Swap("image"+std::to_string(i), "frame"+std::to_string(i));
	}
	
	// Actually we don't want the frame around the logo so let's delete it
	outputCanvas.Remove("frame1");
	
	// This tests that swap won't do anything with invalid names...
	outputCanvas.Swap("image2", "this one");
	
	// This tests that it won't remove anything in the case of an invalid pointer
	outputCanvas.Remove("that one");
	
	// This is our final output. The output canvas draws all its layers in order, blending based on alpha channel
	outputCanvas.draw(out);
	out.writeToFile(OUTPUT_FILE);
}

int main(){
	AssembleOutPNG();
	AssembleCollagePNG();
	return 0;
}
