#ifndef ABOUTMENU_DB
#define ABOUTMENU_DB

#include "Menu.hpp"

class AboutMenu : public Menu
{
private:
	static constexpr char msg1[] = "Made by Alaa Arees (PHOENIX) using Raylib library.";
	static constexpr char msg2[] = "Current version: beta 2.2";
	static constexpr char msg3[] = "this game is open source and built 100% in C++, if you want \nto check the source code or if you have any feedbacks \nfeel free to contact me on: \ndiscord or telegram phoenix_9226 (same username).";
	static constexpr char msg4[] = "Have a nice day!";
	
public:
	AboutMenu ();
	void loop ()  override;
	// void update () override; // no need to override update for main menu.
	void draw () override;
};

#endif // ABOUTMENU_DB