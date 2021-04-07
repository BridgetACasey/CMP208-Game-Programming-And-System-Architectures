//@BridgetACasey

#pragma once

#include <map>

#include "audio_3d.h"

enum class SoundEffectID
{
	NONE = -1,
	INTRO,
	CLICK,
	COLLECTED,
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
	Int32 sampleIndex = -1;
};

class GameAudio
{
protected:
	GameAudio(gef::Platform& platform);

public:
	static GameAudio* create(gef::Platform& platform);

	void initSFX();
	void initMusic();

	void update();

	void playMusic(MusicID id);
	bool isMusicPlaying(MusicID id);

	void loadSoundEffect(SoundEffectID id);
	void playSoundEffect(SoundEffectID id, bool looping);
	void clearSoundEffect(SoundEffectID id);

	void setMasterVolume(float masterVolume_);
	void setMusicVolume(float musicVolume_);
	void setSFXVolume(float sfxVolume_);

	float getMasterVolume();
	float getMusicVolume();
	float getSFXVolume();

	Audio3D* get3D();
	gef::AudioManager* getManager();
	AudioListener& getListener();

private:
	gef::Platform& platform_;

	Audio3D* audio3D;
	gef::AudioManager* audioManager;

	float masterVolume;
	float musicVolume;
	float sfxVolume;

	MusicID activeMusic;

	std::map<SoundEffectID, SoundEffect> sfx;
	std::map<MusicID, const char*> music;
};