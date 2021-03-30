#include "audio_3d.h"

Audio3D::Audio3D(gef::AudioManager* audio_manager) :
	audio_manager_(audio_manager)
{
	setMasterVolume(100.0f);
	setMusicVolume(50.0f);
	setSFXVolume(50.0f);
}

void Audio3D::AddEmitter(const AudioEmitter& emitter)
{
	emitters_.push_back(emitter);
}

void Audio3D::setMasterVolume(float masterVolume_)
{
	masterVolume = masterVolume_;

	audio_manager_->SetMasterVolume(masterVolume);
}

void Audio3D::setMusicVolume(float musicVolume_)
{
	musicVolume = musicVolume_;
}

void Audio3D::setSFXVolume(float sfxVolume_)
{
	sfxVolume = sfxVolume_;
}


void Audio3D::Update()
{
	// make sure audio manager is valid before proceeding
	if (!audio_manager_)
		return;

//	For each emitter
	for (std::vector<AudioEmitter>::iterator emitter = emitters_.begin(); emitter != emitters_.end();)
	{
//		Calculate emitter position in listener local coordinate space
		gef::Vector4 emitter_local_position = listener_.TransformWorld2Local(emitter->position());

		bool delete_emitter = false;


//		If distance is less than emitter range
		float distance = emitter_local_position.Length();
		if (distance < emitter->radius())
		{
			// check to see if one shot sample was playing, but has now stopped
			// remove the emitter if it has stopped
			if (emitter->playing())
			{
				if (!audio_manager_->sample_voice_playing(emitter->voice_id()))
				{
					emitter->SoundStopped();
					delete_emitter = true;
				}
			}

			if (delete_emitter)
			{
				// delete emitter from collection and update iterator
				emitter = emitters_.erase(emitter);
			}
			else
			{
				//		    If sound is not playing on the emitter Then
				if (!emitter->playing())
				{
					//		        Start the sound playing
					int voice_id = audio_manager_->PlaySample(emitter->sfx_id(), emitter->looping());
					if (voice_id != -1)
						emitter->SoundStarted(voice_id);
				}

				// safety check, make sure the emitter is playing before trying to alter the volume settings
				if (emitter->playing())
				{
					// Set the sound volume based on the distance from the emitter
					float volume = sfxVolume * (1.0f - (distance / emitter->radius())) * (masterVolume / 100.0f);

					//		    Set the sound pan based on angle between x-axis and listener->emitter vector
					const gef::Vector4 x_axis(1.0f, 0.0, 0.0f);
					float pan = emitter_local_position.DotProduct(x_axis);

					gef::VolumeInfo volume_info;
					volume_info.volume = volume;
					volume_info.pan = pan;
					audio_manager_->SetSampleVoiceVolumeInfo(emitter->voice_id(), volume_info);
				}
			}
		}
		else
		{
			//		Else If sound is playing on the emitter Then
			if (emitter->playing())
			{
				//		    Stop the sound on the emitter
				if (emitter->voice_id() != -1)
					audio_manager_->StopPlayingSampleVoice(emitter->voice_id());
				emitter->SoundStopped();
			}
		}

		if (!delete_emitter)
		{
			// update iterator
			emitter++;
		}
	}
}