#include <iostream>
#include "raylib.h"
#include "AudioManager.hpp"
#include "global_resources.hpp"

AudioManager::AudioManager ()
{
	InitAudioDevice ();
	cannonBallCurrentIndex = 0;
	
	// dump decryption:
	system ("ren resources\\audio\\launch_cannon_ball.DB_MEDIA launch_cannon_ball.mp3");
	system ("ren resources\\audio\\Dodgy_Blocks_-_Main_Menu_Theme_-_Cosmos.DB_MEDIA Dodgy_Blocks_-_Main_Menu_Theme_-_Cosmos.mp3");
	system ("ren resources\\audio\\Dodgy_Blocks_-_Game_OST_#1_-_Solar.DB_MEDIA Dodgy_Blocks_-_Game_OST_#1_-_Solar.mp3");
	system ("ren resources\\audio\\Dodgy_Blocks_-_Game_OST_#2_-_Array.DB_MEDIA Dodgy_Blocks_-_Game_OST_#2_-_Array.mp3");
	system ("ren resources\\audio\\Dodgy_Blocks_-_Game_OST_#3_-_Reactor.DB_MEDIA Dodgy_Blocks_-_Game_OST_#3_-_Reactor.mp3");
	
	// load resources:
	for (size_t i = 0; i < MAX_CANNON_BALL_SOUNDS; i++){
		cannonBallSoundPool[i] = LoadSound ("resources\\audio\\launch_cannon_ball.mp3");
	}
	menuMusic		= LoadMusicStream ("resources/audio/Dodgy_Blocks_-_Main_Menu_Theme_-_Cosmos.mp3");
	inGameMusic[0]	= LoadMusicStream ("resources/audio/Dodgy_Blocks_-_Game_OST_#1_-_Solar.mp3");
	inGameMusic[1]	= LoadMusicStream ("resources/audio/Dodgy_Blocks_-_Game_OST_#2_-_Array.mp3");
	inGameMusic[2]	= LoadMusicStream ("resources/audio/Dodgy_Blocks_-_Game_OST_#3_-_Reactor.mp3");
	currentMusic = &menuMusic;
	lastPlayedMusicIndex = IN_GAME_MUSIC_COUNT;
	
	menuMusic.looping = 1;
	inGameMusic[0].looping = inGameMusic[1].looping = inGameMusic[2].looping = 0;
	
	PlayMusicStream (*currentMusic);
}

AudioManager::~AudioManager ()
{
	for (size_t i = 0; i < MAX_CANNON_BALL_SOUNDS; i++){
		UnloadSound (cannonBallSoundPool[i]);
	}
	UnloadMusicStream (menuMusic);
	for (size_t i = 0; i < IN_GAME_MUSIC_COUNT; i++){
		UnloadMusicStream (inGameMusic[i]);
	}
	
	// dump encryption:
	system ("ren resources\\audio\\launch_cannon_ball.mp3 launch_cannon_ball.DB_MEDIA");
	system ("ren resources\\audio\\Dodgy_Blocks_-_Main_Menu_Theme_-_Cosmos.mp3 Dodgy_Blocks_-_Main_Menu_Theme_-_Cosmos.DB_MEDIA");
	system ("ren resources\\audio\\Dodgy_Blocks_-_Game_OST_#1_-_Solar.mp3 Dodgy_Blocks_-_Game_OST_#1_-_Solar.DB_MEDIA");
	system ("ren resources\\audio\\Dodgy_Blocks_-_Game_OST_#2_-_Array.mp3 Dodgy_Blocks_-_Game_OST_#2_-_Array.DB_MEDIA");
	system ("ren resources\\audio\\Dodgy_Blocks_-_Game_OST_#3_-_Reactor.mp3 Dodgy_Blocks_-_Game_OST_#3_-_Reactor.DB_MEDIA");
	
	CloseAudioDevice ();
}

void AudioManager::play_cannon_ball_sound (float pitch)
{
	if (!check_setting (ENABLE_SFX)) {return;}
	SetSoundPitch (cannonBallSoundPool[cannonBallCurrentIndex], pitch);
	PlaySound (cannonBallSoundPool[cannonBallCurrentIndex]);
	cannonBallCurrentIndex = (cannonBallCurrentIndex+1) % MAX_CANNON_BALL_SOUNDS;
}

void AudioManager::update (Loops loop)
{
	if (!check_setting (ENABLE_MUSIC)) {return;}
	switch (loop)
	{
		case GAME_LOOP:
			if (!IsMusicStreamPlaying (*currentMusic)){play_next_in_game_music ();}
			break;
			
		case OUT_GAME_MENUS_LOOP:
			// if (lastPlayedMusicIndex != IN_GAME_MUSIC_COUNT){
				// StopMusicStream (*currentMusic);
				// currentMusic = &menuMusic;
				// PlayMusicStream (*currentMusic);
			// }
			// else if (!IsMusicStreamPlaying (*currentMusic)){
				// PlayMusicStream (*currentMusic);
			// }
			break;
			
		case IN_GAME_MENUS_LOOP:
			if (!IsMusicStreamPlaying (*currentMusic)){
				collapse_current_music (0);
				play_next_in_game_music ();
				collapse_current_music (1);
			}
			break;
	}
	
	UpdateMusicStream (*currentMusic);
}

void AudioManager::collapse_current_music (bool collapse)
{
	float newVol = collapse ? COLLAPSING_MUSIC_VOLUME : 1.0f;
	SetMusicVolume (*currentMusic, newVol);
}

void AudioManager::play_next_in_game_music ()
{
	short newIndex;
	do{
		newIndex = random_number (0, IN_GAME_MUSIC_COUNT-1);
	}while (newIndex == lastPlayedMusicIndex);
	currentMusic = &inGameMusic[newIndex];
	lastPlayedMusicIndex = newIndex;
	PlayMusicStream (*currentMusic);
}

void AudioManager::stop_menu_music ()
{
	StopMusicStream (menuMusic);
}

void AudioManager::play_menu_music ()
{
	StopMusicStream (*currentMusic);
	currentMusic = &menuMusic;
	PlayMusicStream (*currentMusic);
}
