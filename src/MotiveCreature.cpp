#include <cmath>
#include "raylib.h"
#include "raymath.h"
#include "MotiveCreature.hpp"

MotiveCreature::MotiveCreature (Vector2 MAX_VELOCITY, Vector2 ACC_FORCE, float MASS, Vector2 initialPos)
	: MAX_VELOCITY (MAX_VELOCITY), ACC_FORCE (ACC_FORCE), MASS (MASS)
{
	position = initialPos;
}

MotiveCreature::~MotiveCreature () {}