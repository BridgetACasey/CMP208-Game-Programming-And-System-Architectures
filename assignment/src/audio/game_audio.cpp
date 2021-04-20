//@BridgetACasey

#include "game_audio.h"

GameAudio::GameAudio(gef::Platform& pltfrm) : platform(pltfrm)
{
    audioManager = gef::AudioManager::Create();

    audio3D = new Audio3D(audioManager);

	setMasterVolume(50.0f);
	setMusicVolume(50.0f);
	sfxVolume = 50.0f;

	initSFX();
	initMusic();
}

GameAudio* GameAudio::create(gef::Platform& pltfrm)
{
    return new GameAudio(pltfrm);
}

void GameAudio::initSFX()	//Loading in all the sfx file paths so they can be called with enum values instead
{
	SoundEffect newSFX{};

	newSFX.filePath = "sfx/mixkit-player-recharging-in-video-game-2041.wav";
	newSFX.sampleIndex = 0;
	sfx[SoundEffectID::INTRO] = newSFX;

	newSFX.filePath = "sfx/mixkit-video-game-retro-click-237.wav";
	newSFX.sampleIndex = 1;
	sfx[SoundEffectID::CLICK] = newSFX;

	newSFX.filePath = "sfx/box_collected.wav";
	newSFX.sampleIndex = 2;
	sfx[SoundEffectID::COLLECTED] = newSFX;

	newSFX.filePath = "sfx/fire.wav";
	newSFX.sampleIndex = 3;
	sfx[SoundEffectID::FIRE] = newSFX;

	newSFX.filePath = "sfx/win.wav";
	newSFX.sampleIndex = 4;
	sfx[SoundEffectID::WIN] = newSFX;

	newSFX.filePath = "sfx/lose.wav";
	newSFX.sampleIndex = 5;
	sfx[SoundEffectID::LOSE] = newSFX;

	/*
	* Keeping a separate sample index values stored means having to load in all sound effects upon launching the application.
	* This is not ideal, but makes it easier to retrieve the sample index instead of loading and unloading. 
	*/

	loadSoundEffect(SoundEffectID::INTRO);
	loadSoundEffect(SoundEffectID::CLICK);
	loadSoundEffect(SoundEffectID::COLLECTED);
	loadSoundEffect(SoundEffectID::FIRE);
	loadSoundEffect(SoundEffectID::WIN);
	loadSoundEffect(SoundEffectID::LOSE);
}

void GameAudio::initMusic()
{
	music[MusicID::MENU] = "sfx/Blazer_Rail.wav";
	music[MusicID::LEVEL] = "sfx/Blazer_Rail_2.wav";
}

void GameAudio::update()
{
	if (audio3D)
	{
		audio3D->Update(sfxVolume);
	}
}

void GameAudio::playMusic(MusicID id)
{
	audioManager->StopMusic();

	if (id == MusicID::NONE)
	{
		return;
	}

	audioManager->LoadMusic(music.at(id), platform);
	audioManager->PlayMusic();

	activeMusic = id;
}

void GameAudio::loadSoundEffect(SoundEffectID id)
{
	audioManager->LoadSample(sfx.at(id).filePath, platform);
}

bool GameAudio::isMusicPlaying(MusicID id)
{
	if (activeMusic == id)
	{
		return true;
	}

	return false;
}

void GameAudio::playSoundEffect(SoundEffectID id, bool looping)
{
	if (id == SoundEffectID::NONE)
	{
		return;
	}

	audioManager->PlaySample(sfx.at(id).sampleIndex, looping);
}

void GameAudio::clearSoundEffect(SoundEffectID id)
{
	audioManager->UnloadSample(sfx.at(id).sampleIndex);
}

void GameAudio::setMasterVolume(float volume)
{
	masterVolume = volume;

	audioManager->SetMasterVolume(masterVolume);
}

void GameAudio::setMusicVolume(float volume)
{
	musicVolume = volume;

	gef::VolumeInfo info;

	info.volume = musicVolume;
	info.pan = 0.0f;

	audioManager->SetMusicVolumeInfo(info);
}

void GameAudio::setSFXVolume(float volume)
{
	sfxVolume = volume;

	gef::VolumeInfo info;

	info.volume = sfxVolume;

	for (auto& effect : sfx)
	{
		Int32 index = sfx.at(effect.first).sampleIndex;

		audioManager->SetSampleVoiceVolumeInfo(index, info);
	}
}

float GameAudio::getMasterVolume()
{
	return masterVolume;
}

float GameAudio::getMusicVolume()
{
	return musicVolume;
}

float GameAudio::getSFXVolume()
{
	return sfxVolume;
}

Audio3D* GameAudio::get3D()
{
	return audio3D;
}

gef::AudioManager* GameAudio::getManager()
{
	return audioManager;
}

AudioListener& GameAudio::getListener()
{
	return audio3D->listener();
}