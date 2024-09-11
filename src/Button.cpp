#include <string>
#include <tuple>
#include <functional>
#include "raylib.h"

#include "Button.hpp"

Button::Button () {}

Button::Button (Rectangle bounds, std::string text, int textSize, 
				std::tuple <Color, Color, Color> normalColors, 
				std::tuple <Color, Color, Color> activeColors,
				std::function <void ()> action,
				KeyboardKey alternativeKey,
				std::function <bool ()> button_toggled_on)
{
	this->bounds = bounds;
	this->text = text;
	this->textSize = textSize;
    std::tie (background, outlines, textColor) = normalColors;
    std::tie (activeBackground, activeOutlines, activeTextColor) = activeColors;
	this->action = action;
	this->alternativeKey = alternativeKey;
	this->button_toggled_on = button_toggled_on;
    
    // text center alignment:
    textWidth = MeasureText (text.c_str(), textSize);
    text_x = bounds.x + bounds.width/2 - textWidth/2;
    text_y = bounds.y + bounds.height/2 -10;
}

void Button::change_colors ()
{
    if (active){
        currentBackground = activeBackground;
        currentOutlines = activeOutlines;
        currentTextColor = activeTextColor;
    }
    else{
        currentBackground = background;
        currentOutlines = outlines;
        currentTextColor = textColor;
    }
}
    
void Button::update (const Camera2D &camera)
{
	Vector2 mousePos = GetScreenToWorld2D (GetMousePosition (), camera);
	
    if (CheckCollisionPointRec (mousePos, bounds)){
        active = 1;
        change_colors ();
    }
    else{
        active = 0;
        change_colors ();
    }

    if ((active && IsMouseButtonReleased (MOUSE_BUTTON_LEFT))
		|| IsKeyReleased (alternativeKey)){
        pressed = 1;
    } else {pressed = 0;}
	
	if (pressed) {action ();}
	if (button_toggled_on()){
		active = 1;
		change_colors ();
	}
}
    
void Button::draw ()
{
    DrawRectangleRounded (bounds, 0.8, 0, currentBackground);
    DrawText (text.c_str(), text_x, text_y, textSize, currentTextColor);
    DrawRectangleRoundedLines ({bounds.x+1, bounds.y+1,
            bounds.width-2, bounds.height-2}, 0.8, 0, 8, currentOutlines);
}