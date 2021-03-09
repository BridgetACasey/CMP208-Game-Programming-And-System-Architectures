//@BridgetACasey

#ifndef _GAME_AUDIO_H
#define _GAME_AUDIO_H

#pragma once

class GameAudio
{
protected:
	GameAudio();

public:
	~GameAudio();

	static GameAudio* create();
};

#endif