#ifndef ABOUTMENU_DB
#define ABOUTMENU_DB

#include "Menu.hpp"

class AboutMenu : public Menu
{
private:
	/* A well formatted version of the description message:
	static constexpr char msg1[] = "Made by Alaa Arees (PHOENIX) using Raylib library.\n
									All music and sound contents are made by Ali Ibrahim (Beyond Electric).\n
									Please read the 'Readme.md' file accompanied in the game folder for more\n
									details about the game, authors and everything else.
									Current version: unknown\n
									this game is open source and written in C++, if you want\n
									to check the source code or if you have any feedbacks\n
									feel free to contact us, contact info are also available\n
									in the 'Readme.md' file.";
	*/
	/* A fucked up version of the same message because Mr. C++ does not support declaring the string on multiple lines: */
	static constexpr char msg1[] = "Made by Alaa Arees (PHOENIX) using Raylib library. \nAll music and sound contents are made by Ali Ibrahim (Beyond Electric). \nPlease read the 'Readme.md' file accompanied in the game folder for \nmore details about the game, authors and everything else. \nCurrent version: unknown \nthis game is open source and written in C++, if you want \nto check the source code or if you have any feedbacks \nfeel free to contact us, contact info are also available \nin the 'Readme.md' file.";
	
public:
	AboutMenu ();
	void loop ()  override;
	void draw () override;
};

#endif // ABOUTMENU_DB