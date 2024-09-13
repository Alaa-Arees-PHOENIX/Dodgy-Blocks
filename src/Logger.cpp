#include <fstream>
#include "Logger.hpp"

void Logger::addListner (Listener& listener)
{
	listeners.push_front (&listener);
}

void Logger::removeListner (Listener& listener)
{
	listeners.remove (&listener);
}

void Logger::logAll ()
{
	for (Listener* listener : listeners){
		listener->logInfo();
	}
}