#ifndef AUDIOMANAGER_DB
#define AUDIOMANAGER_DB

#include <cstddef>
#include "raylib.h"
#include "types.hpp"

class AudioManager
{
public:
	AudioManager ();
	~AudioManager ();
	void play_cannon_ball_sound (float pitch = 1.0f);
	void update (Loops loop); // @PARAMETER: from which loop was this function invoked.
	void collapse_current_music (bool collapse);
	void enter_music_transform_phase (bool enter);
	void play_next_in_game_music ();
	void stop_menu_music ();
	
private:
	Music* currentMusic;
	
	/* set to 'true' when AudioManager should stop a music stream from a certain loop
		and start another music stream in another loop, considering that if the user
		decided to restart the game before the music transformation phase ends AudioManager
		should continue playing a music from inGameMusic instead of menuMusic. */
	bool musicTransformPhase;
	
	/* at which second (relative to current music being played) should AudioManager stop whatever
		inGameMusic is playing and start playing menuMusic (this variable is set when
		enter_music_transform_phase method is invoked. */
	size_t timeToSwitchMusic;
	
	float COLLAPSING_MUSIC_VOLUME = 0.6f; // when game is paused or when musicTransformPhase is true
	
	/* values from 0 to (IN_GAME_MUSIC_COUNT-1) for inGameMusic
		value of IN_GAME_MUSIC_COUNT for menuMusic (invalid index but works for the random music choosing logic */
	short lastPlayedMusicIndex;
	
	static constexpr size_t MAX_CANNON_BALL_SOUNDS = 10;
	size_t cannonBallCurrentIndex;
	Sound cannonBallSoundPool[MAX_CANNON_BALL_SOUNDS];
	Music menuMusic;
	static constexpr size_t IN_GAME_MUSIC_COUNT = 3;
	Music inGameMusic[IN_GAME_MUSIC_COUNT];
};

#endif // AUDIOMANAGER_DB