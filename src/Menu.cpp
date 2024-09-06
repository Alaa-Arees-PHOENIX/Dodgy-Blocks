#include <vector>
#include "raylib.h"
#include "Button.hpp"
#include "Menu.hpp"

void Menu::update (const Camera2D& camera)
{
	for (size_t i=0; i<buttons.size (); i++){buttons[i].update (camera);}
}

void Menu::draw ()
{
	for (size_t i=0; i<buttons.size (); i++){buttons[i].draw ();}
}

void Menu::add_button (Button b)
{
	buttons.push_back (b);
}

Button& Menu::operator[] (size_t i) {return buttons[i];}

void Menu::draw_message_aligned (Button& button, const char msg[], Color color)
{
    float tempSize, temp_x;
    tempSize = button.get_size () + 15;
    temp_x = button.get_x() - MeasureText (msg, tempSize) - 50;
    DrawText (msg, temp_x, button.get_y (), tempSize, color);
}