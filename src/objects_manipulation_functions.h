#pragma once
#include "game_objects.h"

/////////////////////////////// DECLARATIONS /////////////////////////////////
void draw_aligned_msg (char msg[], button, Color);

//////////////////////////////////////////////////////////////////////////////

/////////////////////////////// DEFENITIONS //////////////////////////////////
void draw_aligned_msg (char msg[], button B, Color c)
{
    float tempSize, temp_x;
    
    tempSize = B.get_size () + 15;
    temp_x = B.get_x() - MeasureText (msg, tempSize) - 50;
    DrawText (msg, temp_x, B.get_y (), tempSize, c);
}