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
	void play_next_in_game_music ();
	void stop_menu_music ();
	void play_menu_music ();
	
private:
	Music* currentMusic;
	
	static constexpr float COLLAPSING_MUSIC_VOLUME = 0.4f; // when game is paused or inside GameOverMenu
	
	/* values from 0 to (IN_GAME_MUSIC_COUNT-1) for inGameMusic
		value of IN_GAME_MUSIC_COUNT for menuMusic (invalid index but works for the random music choosing logic */
	short lastPlayedMusicIndex;
	
	static constexpr size_t MAX_CANNON_BALL_SOUNDS = 6;
	size_t cannonBallCurrentIndex;
	Sound cannonBallSoundPool[MAX_CANNON_BALL_SOUNDS];
	Music menuMusic;
	static constexpr size_t IN_GAME_MUSIC_COUNT = 3;
	Music inGameMusic[IN_GAME_MUSIC_COUNT];
};

#endif // AUDIOMANAGER_DB