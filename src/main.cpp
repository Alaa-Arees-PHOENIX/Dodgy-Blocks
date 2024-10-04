#include <ctime>
#include "raylib.h"
#include "global_resources.hpp"

void show_intro ();

int main ()
{
	srand (time (NULL));
	
	create_globals ();
	
	show_intro ();
	
	MAIN_MENU.loop ();
	
	destroy_globals ();
	
	return 0;
}

void show_intro ()
{
	char msg[] = "Alaa Arees ~ PHOENIX";
	int fontSize = 65;
	Color textColor = dark_mode_processor (RED);
	Color backgroundColor = dark_mode_processor (RAYWHITE);
	float fadingFactor = 1.0f;
	
	while (fadingFactor > 0){
		BeginDrawing ();
		ClearBackground (backgroundColor);
		BeginMode2D (CAMERA);
		DrawText (msg, -MeasureText (msg, fontSize)/2.0f, -fontSize/2.0f, fontSize, textColor);
		if (GetTime () > 3.0){
			textColor = Fade (textColor, fadingFactor);
			fadingFactor -= 0.01;
		}
		EndMode2D ();
		EndDrawing ();
	}
}
