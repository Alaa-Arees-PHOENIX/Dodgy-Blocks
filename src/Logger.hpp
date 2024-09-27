#ifndef LOGGER_DB
#define LOGGER_DB

#include <forward_list>

class Logger
{
public:
	class Listener
	{
	public:
		virtual void log_info (	int logTime,
								bool useDefaultLogFile = 1,
								const char* alternativeFile = "\0") = 0;
	};
	
	Logger ();
	void add_listener (Listener*);
	void remove_listener (Listener*);
	void update (float dt);
	void log_all ();
	
	static constexpr char LINE_BREAK[] = "\n ----------------------------------- \n";

private:
	std::forward_list <Listener*> listeners;
	double timeSinceGameLaunch;
};

#endif // LOGGER_DB