#include <ctime>
#include "raylib.h"
#include "Singleton.hpp"
#include "global_resources.hpp"

bool choose_screen_mode()
{
	InitWindow (1012, 569, "Dodgy Blocks");
	
	while (true){
		
		// update:
		if (IsKeyPressed (KEY_ONE)) {CloseWindow (); return 0;}
		if (IsKeyPressed (KEY_TWO)) {CloseWindow (); return 1;}
		
		// draw:
		BeginDrawing ();
		ClearBackground (WHITE);
		DrawText (	"Press '1' to play in windowed mode\nPress '2' to play in full screen mode",
					253, 284, 20, RED);
		EndDrawing ();
	}
}

int main ()
{
	srand (time (NULL));
	
	// bool screenMode = choose_screen_mode ();
	create_globals (0);
	
	MAIN_MENU.loop ();
	
	destroy_globals ();
	
	return 0;
}
