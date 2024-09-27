#ifndef AUDIOMANAGER_DB
#define AUDIOMANAGER_DB

#include <cstddef>
#include "raylib.h"

class AudioManager
{
public:
	AudioManager ();
	~AudioManager ();
	void play_cannon_ball_sound (float pitch = 1.0f);
	
private:
	static constexpr size_t MAX_CANNON_BALL_SOUNDS = 10;
	size_t cannonBallCurrentIndex;
	Sound cannonBallSoundPool[MAX_CANNON_BALL_SOUNDS];
};

#endif // AUDIOMANAGER_DB