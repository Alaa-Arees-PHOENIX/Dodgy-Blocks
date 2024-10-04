#ifndef TYPES_DB
#define TYPES_DB

enum Difficulty {EASY, MEDIUM, HARD, INSANE};

enum GameMode {SANDBOX, ARCADE, FRENZY};

enum Directions {UP_DIR, DOWN_DIR, LEFT_DIR, RIGHT_DIR}; // unused

enum Settings
{
	SHOW_FPS		=	1 << 0,
	DARK_MODE		=	1 << 1
};

/* defines various loop objects like GameWorld::loop() or MainMenu::loop() in a
	format suitable for 'if' and 'switch' statements, that is, an enum... */
enum Loops
{
	OUT_GAME_MENUS_LOOP, // used for MAIN_MENU, SETTINGS_MENU and ABOUT_MENU
	GAME_LOOP, // used when the game is actually running
	IN_GAME_MENUS_LOOP //used for PAUSE_MENU and GAME_OVER_MENU
};

struct Range
{
	/*	range min/max */
	int rMin;
	int rMax;
};

#endif // TYPES_DB