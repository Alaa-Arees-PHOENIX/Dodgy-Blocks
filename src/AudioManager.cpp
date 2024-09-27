#include "raylib.h"
#include "AudioManager.hpp"

AudioManager::AudioManager ()
{
	InitAudioDevice ();
	cannonBallCurrentIndex = 0;
	for (size_t i = 0; i < MAX_CANNON_BALL_SOUNDS; i++){
		cannonBallSoundPool[i] = LoadSound ("resources/audio/launch_cannon_ball.mp3");
	}
}

AudioManager::~AudioManager ()
{
	for (size_t i = 0; i < MAX_CANNON_BALL_SOUNDS; i++){
		UnloadSound (cannonBallSoundPool[i]);
	}
	CloseAudioDevice ();
}

void AudioManager::play_cannon_ball_sound (float pitch)
{
	SetSoundPitch (cannonBallSoundPool[cannonBallCurrentIndex], pitch);
	PlaySound (cannonBallSoundPool[cannonBallCurrentIndex]);
	cannonBallCurrentIndex = (cannonBallCurrentIndex+1) % MAX_CANNON_BALL_SOUNDS;
}

