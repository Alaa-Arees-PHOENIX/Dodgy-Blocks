#include <cmath>
#include <fstream>
#include "raylib.h"
#include "raymath.h"
#include "MotiveCreature.hpp"
#include "global_resources.hpp"

MotiveCreature::MotiveCreature (Vector2 MAX_VELOCITY, Vector2 ACC_FORCE, float MASS, Vector2 initialPos)
	: MAX_VELOCITY (MAX_VELOCITY), ACC_FORCE (ACC_FORCE), MASS (MASS)
{
	position = initialPos;
}

MotiveCreature::~MotiveCreature () {}

void MotiveCreature::log_info (int logTime, bool useDefaultLogFile, const char* alternativeFile)
{
	std::ofstream logFile;
	if (useDefaultLogFile){
		logFile.open("log/MotiveCreature_log.txt", std::ios_base::app);
	}
	else {logFile.open (alternativeFile, std::ios_base::app);}
	
	logFile << Logger::LINE_BREAK;
	
	logFile << "MotiveCreature instance, logged at " << logTime << '\n';
	logFile << "address: " << this << '\n';
	logFile << "position = " << to_string (position) << '\n';
	logFile << "velocity = " << to_string (velocity) << '\n';
	logFile << "max velocity = " << to_string (MAX_VELOCITY) << '\n';
	logFile << "acceleration force = " << to_string (ACC_FORCE) << '\n';
	logFile << "mass = " << MASS << '\n';
	
	logFile << Logger::LINE_BREAK;
	
	logFile.close();
}
