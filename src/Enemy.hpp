#ifndef ENEMY_DB
#define ENEMY_DB

#include "Logger.hpp"

class Enemy : virtual public Logger::Listener
{
protected:
	const int SPAWN_TIME, DEATH_TIME; // in seconds
	
protected: // no instantiation without inheritance
	Enemy (int lifespan);
	
public:
	virtual ~Enemy ();
	virtual void update (float dt) = 0;
	virtual void draw () = 0;
	bool life_has_ended ();
	void logInfo (	int logTime,
					bool useDefaultLogFile = 1,
					const char* alternativeFile = "\0") override;
	
	int get_spaw_time () const	{return SPAWN_TIME;}
	int get_death_time () const	{return DEATH_TIME;}
};

#endif // ENEMY_DB