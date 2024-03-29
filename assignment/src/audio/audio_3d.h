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

	void Update(float sfxVolume);

	void AddEmitter(const AudioEmitter& emitter);

	inline AudioListener& listener() { return listener_; }

private:
	gef::AudioManager* audio_manager_;
	AudioListener listener_;

	std::vector<AudioEmitter> emitters_;
};

#endif // _AUDIO_3D_H