#ifndef _AUDIO_3D_H
#define _AUDIO_3D_H

#include <audio/audio_manager.h>
#include "audio_listener.h"
#include "audio_emitter.h"
#include <vector>

class Audio3D
{
public:
	Audio3D(gef::AudioManager* audio_manager);

	void Update();

	void AddEmitter(const AudioEmitter& emitter);

	void setMasterVolume(float masterVolume_);
	void setMusicVolume(float musicVolume_);
	void setSFXVolume(float sfxVolume_, Int32 sfxID);

	float getMasterVolume();
	float getMusicVolume();
	float getSFXVolume();

	inline AudioListener& listener() { return listener_; }

	gef::AudioManager* manager() { return audio_manager_; }

private:
	gef::AudioManager* audio_manager_;
	AudioListener listener_;

	std::vector<AudioEmitter> emitters_;

	float masterVolume;
	float musicVolume;
	float sfxVolume;
};

#endif // _AUDIO_3D_H