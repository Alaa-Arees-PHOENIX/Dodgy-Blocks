#ifndef MENU_DB
#define MENU_DB

#include <vector>
#include "raylib.h"
#include "Button.hpp"
// class Button;

class Menu
{
protected:
	std::vector <Button> buttons;
	
public:
	virtual void loop () = 0;
	void update (const Camera2D& camera);
	virtual void draw ();
	void add_button (Button b);
	Button& operator[] (int i);
	
protected:
	Menu () {}
	void draw_message_aligned (Button& button, const char msg[], Color color);
};

#endif // MENU_DB