#ifndef TYPES_DB
#define TYPES_DB

enum Difficulty {EASY, MEDIUM, HARD, INSANE};

enum Directions {UP_DIR, DOWN_DIR, LEFT_DIR, RIGHT_DIR};

enum Settings
{
	SANDBOX			=	1 << 0,
	SHOW_FPS		=	1 << 1
};

struct Range
{
	/*	range min/max */
	int rMin;
	int rMax;
};

#endif // TYPES_DB