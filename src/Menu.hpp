#ifndef MENU_DB
#define MENU_DB

#include <vector>
#include "raylib.h"
#include "Button.hpp"
// class Button;

class Menu
{
public:
	virtual void loop () = 0;
	void update (const Camera2D& camera);
	virtual void draw ();
	void add_button (Button b);
	Button& operator[] (size_t i);
	
protected:
	Menu () {}
	virtual ~Menu() {};
	void draw_message_aligned (Button& button, const char msg[], Color color);
	
protected:
	std::vector <Button> buttons;
};

#endif // MENU_DB