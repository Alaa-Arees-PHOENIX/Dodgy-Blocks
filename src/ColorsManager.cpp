#include "raylib.h"
#include "ColorsManager.hpp"

ColorsManager::ColorsManager ()
	: darkMode (0)
{
	darkVersionOfColor = (std::unordered_map <Color, Color>)
	{
		{WHITE, NEIL},
		{RAYWHITE, ALIBLACK},
		{GRAY, DARKGRAY},
		{LIGHTGRAY, DARKGRAY},
		{BLACK, LIGHTGRAY}
	};
}

ColorsManager::~ColorsManager ()
{
	darkVersionOfColor.clear();
}


Color ColorsManager::color_mode (const Color& c1)
{
	if (!darkMode) {return c1;}
	if (darkVersionOfColor.count (c1)) {return darkVersionOfColor[c1];}
	// else return the inverse whatever it is:
	Color c2 = c1;
	unsigned short highestVal = std::max (c1.r, std::max (c1.g, c1.b));
	c2.r = (highestVal - c2.r);
	c2.g = (highestVal - c2.g);
	c2.b = (highestVal - c2.b);
	return c2;
}

Color ColorsManager::color_mode (const Color&& c1)
{
	if (!darkMode) {return c1;}
	if (darkVersionOfColor.count (c1)) {return darkVersionOfColor[c1];}
	// else return the inverse whatever it is:
	Color c2 = c1;
	unsigned short highestVal = std::max (c1.r, std::max (c1.g, c1.b));
	c2.r = (highestVal - c2.r);
	c2.g = (highestVal - c2.g);
	c2.b = (highestVal - c2.b);
	return c2;
}