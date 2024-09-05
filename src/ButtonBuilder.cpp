#include "ButtonBuilder.hpp"
#include <tuple>
#include <functional>
#include "raylib.h"
#include "Button.hpp"

ButtonBuilder::ButtonBuilder ( std::tuple <Color, Color, Color> defaultNormalColors,
					std::tuple <Color, Color, Color> defaultActiveColors,
					int textSize)
{
	this->defaultNormalColors = defaultNormalColors;
	this->defaultActiveColors = defaultActiveColors;
	this->textSize = textSize;
}
	
Button ButtonBuilder::build	(	std::string text,
								Rectangle bounds,
								std::function <void ()> action,
								KeyboardKey alternativeKey)
{
	return Button (bounds, text, textSize, defaultNormalColors, defaultActiveColors, action, alternativeKey);
}