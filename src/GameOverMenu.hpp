#ifndef GAMEOVERMENU_DB
#define GAMEOVERMENU_DB

#include "Menu.hpp"

class GameOverMenu : public Menu
{
public:
	GameOverMenu ();
	void loop ()  override;
	void draw () override;
	
private:
	static constexpr char msg1[] = "Player 1 has survived ";
	static constexpr char msg2[] = "Player 2 has survived ";
	static constexpr char msg3[] = "Player 3 has survived ";
};

#endif // GAMEOVERMENU_DB