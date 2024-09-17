#include <ctime>
#include "raylib.h"
#include "global_resources.hpp"

int main ()
{
	srand (time (NULL));
	
	create_globals ();
	
	MAIN_MENU.loop ();
	
	destroy_globals ();
	
	return 0;
}
