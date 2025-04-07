/**
 * @file shuffleCards.cpp
 * @author Anna LaValle
 * @date Created: Spring 2025
 */

//TODO you will need to modify this function (called from main.cpp)
void shuffleCards(){

	// Let's prepare the output file
	const std::string OUTPUT_FILE = "shuffle.png";

	// The images of ten playing cards are located in Images directory, named 1.jpg - 10.jpg
	std::string INPUT_FILE = "Images/";
	
	// The output should be the 10 cards that are shuffled on the canvas.png image
	// Shuffling should be done using the list shuffle function (from list.cpp)
	PNG out("Images/canvas.png");
	int WIDTH = out.width();
	int HEIGHT = out.height();
	
	// Let's use this variable so it'd be easier to change the number later
	const int num_cards = 10;
	
	// Define the output canvas, we will use its layers for the cards images
	Canvas outputCanvas;
	
	// Define the png layers
	// To properly shuffle the images you will need to use the List object in some way
	List<PNGLayer> list;
	
	// Load the card images into the list.
        // Your job is to update the lines below to properly populate the list with all the cards,
	// then to properly shuffle them,
	// and then to arrange them on the output canvas in the shuffled order.
	
	// TODO, update the lines below as needed. Currently, the code works for one layer(card) only.
	
	// Each card layer should be defined as a sample layer below.
	// No need to reposition the cards yet, as we will need to shuffle them first.
	PNGLayer p(WIDTH, HEIGHT, Vector2(0.0, 0.0), Vector2(1.0, 1.0), RGBAPixel(255,255,255,255),"1");
		
	// Read each layer from the corresponging image file
	p.readFromFile(INPUT_FILE + "1.png");

	// Place the layers in the list
	list.insertFront(p);

	// Now shuffle the layers
	// You MUST use the shuffle function from the List class (our Autograder will check for it)
	list.shuffle();
	
	// Now, as the cards are properly shuffled we need to reposition them
	// We want them to be placed properly on the canvas.
	int index = 0;
	// index should start with 0 to go up to the size of the list according to the shuffle function
	// This ist the way the layers should be ordered in the Canvas object.
	// Set up the position of each layer according to index and dimensions
	p.SetPosition(Vector2(WIDTH/100 + (WIDTH-WIDTH/9)/num_cards * index, HEIGHT/4));
	
	//Add layers to the canvas
	outputCanvas.Add(p);
	
	// Draw the canvas with properly shuffled layers on the final PNG object.
	// This needs to be done just once after all the layers are added.
	outputCanvas.draw(out);
	
	// Write the final PNG to the output file
	out.writeToFile(OUTPUT_FILE);
}
