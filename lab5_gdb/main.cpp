/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 *
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include "list.h"
#include "png.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "canvas.h"
#include "pnglayer.h"


List<RGBAPixel> imageToList(PNG const & img)
{
	List<RGBAPixel> list;
	for (size_t i = 0; i < img.width(); i++)
	{
		for (size_t j = 0; j < img.height(); j++)
		{
			list.insertFront(img(i,j));
		}
	}
	list.reverse();
	return list;
}

PNG listToImage(List<RGBAPixel> const & list, size_t width, size_t height)
{
	PNG ret;
	ret.resize(width, height);
	size_t x = 0;
	size_t y = 0;
	int i = 0;
	for (auto& pixel: list)
	{
		ret(x,y) = pixel;
		y++;
		if (y == height)
		{
			y = 0;
			x++;
		}
	}
	return ret;
}

void checkSoln(std::string const & test, PNG const & out, std::string const & soln_file)
{
	PNG soln;
	soln.readFromFile(soln_file.c_str());

	if (!(soln == out))
		std::cerr << "[" << test << "]: Image does not match " << soln_file << std::endl;
	else
		std::cout << "[" << test << "]: Images match!" << std::endl;
}

void testInsertFront()
{
	std::cout << "[main]: " << __func__ << "()" << std::endl;

	// test insertFront
	List<int> list;
	for (int i = 1; i <= 10; i++)
		list.insertFront(i);

	std::cout << "[testInsertFront]: " << list << std::endl;
	std::cout << "[testInsertFront]: size: " << list.size() << std::endl;
	if (list.size() != 10)
		std::cout << "[testInsertFront]: Incorrect size" << std::endl;
}

void testInsertBack()
{
	std::cout << "[main]: " << __func__ << "()" << std::endl;

	// test insertBack
	List<int> list;
	for (int i = 1; i <= 10; i++)
		list.insertBack(i);

	std::cout << "[testInserts]: " << list << std::endl;
	std::cout << "[testInserts]: size: " << list.size() << std::endl;
	if (list.size() != 10)
		std::cout << "[testInserts]: Incorrect size" << std::endl;
}

void testReverse()
{
	std::cout << "[main]: " << __func__ << "()" << std::endl;
	PNG in("Images/in.png");

	List<RGBAPixel> list = imageToList(in);
	list.reverse();

	PNG out = listToImage(list, in.width(), in.height());
	out.writeToFile("reverse.png");

	checkSoln(__func__, out, "soln_reverse.png");
}

#include "shuffleCards.cpp"

void testShuffle()
{
	std::cout << "[main]: " << __func__ << "()" << std::endl;

	List<int> list;
	for (int i = 10; i > 0; i--)
		list.insertFront(i);
	std::cout << "[testShuffle]: before " << list << std::endl;
	list.shuffle();
	std::cout << "[testShuffle]: after " << list << std::endl;

	shuffleCards();
}

int main(int argc, char ** argv)
{
	std::vector<std::string> args(argv, argv+argc);
	if (argc == 1 || args[1] == "all")
	{
		testInsertFront();
		testInsertBack();
		testReverse();
		testShuffle();
	}
	else
	{
		if (args[1] == "front")
		  testInsertFront();
		else if (args[1] == "back")
		  testInsertBack();
		else if (args[1] == "reverse")
		  testReverse();
		else if (args[1] == "shuffle")
		  testShuffle();
	}
	return 0;
}

