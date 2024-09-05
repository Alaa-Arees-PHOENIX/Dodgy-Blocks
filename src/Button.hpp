#ifndef BUTTON_DB
#define BUTTON_DB

#include <string>
#include <tuple>
#include <functional>
#include "raylib.h"

class Button
{
private:
	Rectangle bounds;
	std::string text;
	int textSize, textWidth, text_x, text_y;
	KeyboardKey alternativeKey = KEY_NULL; // alternative method to press the button
	bool active = 0, pressed = 0;
	std::function <void ()> action;
	
	Color background, outlines, textColor;
	Color activeBackground, activeOutlines, activeTextColor; //when mouse hover over button
	Color currentBackground, currentOutlines, currentTextColor;
	
public: // setters and getters are defined here to be inlined    
	float get_x () 			{return bounds.x;}
	float get_y () 			{return bounds.y;}
	float get_width () 		{return bounds.width;}
	float get_height () 	{return bounds.height;}
	float get_size () 		{return textSize;}
	bool is_active () 		{return active;}
	bool is_pressed () 		{return pressed;}
	void activate (bool b) 	{active = b;}
	void press (bool b) 	{pressed = b;}
	
	Button ();
	Button (Rectangle bounds, std::string text, int textSize, 
            std::tuple <Color, Color, Color> normalColors, 
            std::tuple <Color, Color, Color> activeColors,
			std::function <void ()> action,
			KeyboardKey alternativeKey);
	
    void change_colors ();
    void update (const Camera2D &camera);
    void draw ();
};

#endif // BUTTON_DB