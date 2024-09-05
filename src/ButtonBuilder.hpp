/***********************************
*		@DESCRIPTION
*	Build buttons that follows a certain pattern.
*	Set defaultNormalColors, defaultActiveColors, textSize, and verticalSpacing
*	to make a bunch of buttons that looks similar
*	*NOTE: verticalSpacing is not a const value but it is calculated
*	each time with a fixed formula
***********************************/

#ifndef BUTTONBUILDER_DB
#define BUTTONBUILDER_DB

#include <tuple>
#include <string>
#include <functional>
#include "raylib.h"

class Button;

class ButtonBuilder
{
	private:
	std::tuple <Color, Color, Color> defaultNormalColors, defaultActiveColors;
	int textSize;
	
	public:
	ButtonBuilder ( std::tuple <Color, Color, Color> defaultNormalColors,
					std::tuple <Color, Color, Color> defaultActiveColors,
					int textSize);
	
	Button build (	std::string text,
					Rectangle bounds,
					std::function <void ()> action,
					KeyboardKey alternativeKey = KEY_NULL);
};

#endif // BUTTONBUILDER_DB