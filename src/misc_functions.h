#pragma once
#include <cmath>
#include <algorithm>
#include "raylib.h"

/////////////////////////////// DECLARATIONS /////////////////////////////////
void window_initilize (float &screenWidth, float &screenHeight);
float random_number (int, int); // rand in range
double lerp (float, float, float); // search for "lerp functions"

double vector_length (Vector2);
Vector2 form_vector (Vector2, Vector2); // form a vector from 2 points
double distance (Vector2, Vector2); // measure the euclidean distance between two points

bool circle_collide_vertical_line (Vector2, int, Vector2, Vector2);
bool circle_collide_horizontal_line(Vector2, int, Vector2, Vector2);

//////////////////////////////////////////////////////////////////////////////

/////////////////////////////// DEFENITIONS //////////////////////////////////
void window_initilize (float &screenWidth, float &screenHeight)
{
    InitWindow (0, 0, "DODGY BLOCKS");
    int monitor = GetCurrentMonitor ();
    screenWidth = GetMonitorWidth (monitor);
    screenHeight = GetMonitorHeight (monitor);
    SetWindowSize (screenWidth, screenHeight);
    // ToggleFullscreen ();
}

double lerp (float initialPos, float targetPos, float lerpSpeed)
{
    return initialPos*(1-lerpSpeed) + targetPos*lerpSpeed;
}

float random_number (int Min, int Max)
{
    return rand () % (Max - Min +1) + Min;
}

//////////////

double vector_length (Vector2 v)
{
    return sqrt (v.x*v.x + v.y*v.y);
}

Vector2 form_vector (Vector2 startPoint, Vector2 endPoint)
{
    return {endPoint.x - startPoint.x, endPoint.y - startPoint.y};
}

double distance (Vector2 p1, Vector2 p2)
{
    return vector_length (form_vector (p1, p2));
}

//////////////

bool circle_collide_vertical_line (Vector2 center, int radius,
                                           Vector2 lineBegin, Vector2 lineEnd)
{
    Vector2 projectionEndPoint; // start point is center
    projectionEndPoint.x = lineBegin.x;
    projectionEndPoint.y = center.y;
    return (radius >= distance (center, projectionEndPoint))
            && (center.y >= lineBegin.y && center.y <= lineEnd.y);
}

bool circle_collide_horizontal_line (Vector2 center, int radius,
                                           Vector2 lineBegin, Vector2 lineEnd)
{
    Vector2 projectionEndPoint; // start point is center
    projectionEndPoint.x = center.x;
    projectionEndPoint.y = lineBegin.y; // or end
    return (radius >= distance (center, projectionEndPoint))
            && (center.y >= lineBegin.y && center.y <= lineEnd.y);
}

//////////////////////////////////////////////////////////////////////////////