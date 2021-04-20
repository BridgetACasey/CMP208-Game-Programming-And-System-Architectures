//@BridgetACasey

#ifndef _GAME_AUDIO_H
#define _GAME_AUDIO_H

#pragma once

#include <map>

#include "audio_3d.h"

enum class SoundEffectID
{
	NONE = -1,
	INTRO,
	CLICK,
	COLLECTED,
	FIRE,
	WIN,
	LOSE
};

enum class MusicID
{
	NONE = -1,
	MENU,
	LEVEL
};

struct SoundEffect
{
	const char* filePath = 0;
	//The index of the sound effect within the 'samples' vector of the gef::AudioManager class
	//Not ideal, but stored here because the samples vector cannot otherwise be accessed from outside gef
	Int32 sampleIndex = -1;
};

//Wrapper class for audio-related functions
class GameAudio
{
protected:
	GameAudio(gef::Platform& pltfrm);

public:
	static GameAudio* create(gef::Platform& pltfrm);

	void initSFX();
	void initMusic();

	void update();

	void playMusic(MusicID id);
	bool isMusicPlaying(MusicID id);

	void loadSoundEffect(SoundEffectID id);
	void playSoundEffect(SoundEffectID id, bool looping);
	void clearSoundEffect(SoundEffectID id);

	void setMasterVolume(float volume);
	void setMusicVolume(float volume);
	void setSFXVolume(float volume);

	float getMasterVolume();
	float getMusicVolume();
	float getSFXVolume();

	Audio3D* get3D();
	gef::AudioManager* getManager();
	AudioListener& getListener();

private:
	gef::Platform& platform;

	Audio3D* audio3D;
	gef::AudioManager* audioManager;

	float masterVolume;
	float musicVolume;
	float sfxVolume;

	MusicID activeMusic;

	std::map<SoundEffectID, SoundEffect> sfx;
	std::map<MusicID, const char*> music;
};

#endif	//_GAME_AUDIO_H