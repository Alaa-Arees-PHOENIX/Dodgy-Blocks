#include "raylib.h"
#include "Timer.hpp"
#include "global_resources.hpp"

Timer::Timer ()
{
	textSize = 16;
	currentTime = 0;
	Vector2 pos = GetScreenToWorld2D ({0.9f*CURRENT_SCREEN_WIDTH, 0.05f*CURRENT_SCREEN_HEIGHT}, CAMERA);
	bounds = {pos.x, pos.y, BASE_WIDTH, BASE_HEIGHT};
	text_y = bounds.y + bounds.height/2 - 7.4;
}

void Timer::reset ()
{
	Vector2 pos	= GetScreenToWorld2D ({0.9f*CURRENT_SCREEN_WIDTH, 0.05f*CURRENT_SCREEN_HEIGHT}, CAMERA);
	currentTime		= 0;
	bounds.width	= BASE_WIDTH;
	bounds.height	= BASE_HEIGHT;
	bounds.x		= pos.x;
	bounds.y		= pos.y;
	text_y			= bounds.y + bounds.height/2 - 7.4;
}

void Timer::update (float dt)
{
	currentTime += dt;
    float textWidth = MeasureText (TextFormat ("%i", (int)currentTime), textSize);
    text_x = bounds.x + bounds.width/2 - textWidth/2;
    if (textWidth >= bounds.width + 7.4) {bounds.width += 7.4;}
}

void Timer::draw ()
{
    DrawRectangleRounded (bounds, 0.8, 0, BLACK);
    DrawText (TextFormat ("%i", (int)currentTime), text_x, text_y, textSize, WHITE);
    DrawRectangleRoundedLines ({bounds.x+1, bounds.y+1, bounds.width-2, bounds.height-2},
								0.8, 0, 8, GRAY);
}