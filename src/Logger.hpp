#ifndef LOGGER_DB
#define LOGGER_DB

#include <forward_list>

class Logger
{
public:
	class Listener
	{
	public:
		virtual void logInfo (bool useDefaultOutputFile = 1, const char* alternativePath = "\0") = 0;
	};
	
	void addListner (Listener&);
	void removeListner (Listener&);
	void logAll ();
	
private:
	std::forward_list <Listener*> listeners;
};

#endif // LOGGER_DB