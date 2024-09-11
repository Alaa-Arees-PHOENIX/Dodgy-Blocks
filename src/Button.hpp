#ifndef BUTTON_DB
#define BUTTON_DB

#include <string>
#include <tuple>
#include <functional>
#include "raylib.h"

class Button
{
	
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
			KeyboardKey alternativeKey = KEY_NULL,
			std::function <bool ()> button_toggled_on = [] () -> bool {return false;});
	
    void change_colors ();
    void update (const Camera2D &camera);
    void draw ();
	
private:
	Rectangle bounds;
	std::string text;
	int textSize, textWidth, text_x, text_y;
	
	/* alternative method to press the button */
	KeyboardKey alternativeKey = KEY_NULL;
	
	bool active = 0, pressed = 0;
	
	/* a set of instructions the button do when pressed, could be anything */
	std::function <void ()> action;
	
	/* a set of conditions, when it returns true the button will change it's colors to active state
		indicating that it is toggled on, this method is only used for settings buttons with several options*/
	std::function <bool ()> button_toggled_on;
	
	Color background, outlines, textColor;
	Color activeBackground, activeOutlines, activeTextColor; //when mouse hover over button
	Color currentBackground, currentOutlines, currentTextColor;
};

#endif // BUTTON_DB