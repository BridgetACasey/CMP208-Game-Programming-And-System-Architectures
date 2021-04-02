#include "game_audio.h"

GameAudio::GameAudio(gef::Platform& platform) : platform_(platform)
{
    audioManager = gef::AudioManager::Create();

    audio3D = new Audio3D(audioManager);

	setMasterVolume(100.0f);
	setMusicVolume(100.0f);
	sfxVolume = 100.0f;

	initSFX();
	initMusic();
}

GameAudio* GameAudio::create(gef::Platform& platform)
{
    return new GameAudio(platform);
}

void GameAudio::initSFX()
{
	SoundEffect newSFX{};

	newSFX.filePath = "mixkit-player-recharging-in-video-game-2041.wav";
	newSFX.sampleIndex = 0;
	sfx[SoundEffectID::INTRO] = newSFX;

	newSFX.filePath = "mixkit-video-game-retro-click-237.wav";
	newSFX.sampleIndex = 1;
	sfx[SoundEffectID::CLICK] = newSFX;

	newSFX.filePath = "box_collected.wav";
	newSFX.sampleIndex = 2;
	sfx[SoundEffectID::COLLECTED] = newSFX;

	newSFX.filePath = "win.wav";
	newSFX.sampleIndex = 3;
	sfx[SoundEffectID::WIN] = newSFX;

	newSFX.filePath = "lose.wav";
	newSFX.sampleIndex = 4;
	sfx[SoundEffectID::LOSE] = newSFX;
}

void GameAudio::initMusic()
{
	const char* newMusic;

	newMusic = "Blazer_Rail.wav";
	music[MusicID::MENU] = newMusic;

	newMusic = "Blazer_Rail_2.wav";
	music[MusicID::LEVEL] = newMusic;
}

void GameAudio::update()
{
	if (audio3D)
	{
		audio3D->Update();
	}
}

void GameAudio::playMusic(MusicID id)
{
	audioManager->StopMusic();

	if (id == MusicID::NONE)
	{
		return;
	}

	audioManager->LoadMusic(music.at(id), platform_);
	audioManager->PlayMusic();
}

void GameAudio::loadSoundEffect(SoundEffectID id)
{
	audioManager->LoadSample(sfx.at(id).filePath, platform_);
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

void GameAudio::setMasterVolume(float masterVolume_)
{
	masterVolume = masterVolume_;

	audioManager->SetMasterVolume(masterVolume);
}

void GameAudio::setMusicVolume(float musicVolume_)
{
	musicVolume = musicVolume_;

	gef::VolumeInfo info;

	info.volume = musicVolume;
	info.pan = 0.0f;

	audioManager->SetMusicVolumeInfo(info);
}

void GameAudio::setSFXVolume(float sfxVolume_, SoundEffectID id)
{
	sfxVolume = sfxVolume_;

	gef::VolumeInfo info;

	if (audioManager->GetSampleVoiceVolumeInfo(sfx.at(id).sampleIndex, info) > -1)
	{
		info.volume = sfxVolume;
		info.pan = 0.0f;

		audioManager->SetSampleVoiceVolumeInfo(sfx.at(id).sampleIndex, info);
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