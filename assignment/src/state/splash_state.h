//@BridgetACasey

#ifndef _SPLASH_STATE_H
#define _SPLASH_STATE_H

#pragma once

#include "state.h"

#include "graphics/sprite.h"

class SplashState : public State
{
protected:
	SplashState(gef::Platform& platform);

public:
	static SplashState* create(gef::Platform& platform);

	void setup() override;

	void onEnter() override;
	void onExit() override;

	void handleInput() override;
	bool update(float deltaTime) override;
	void render() override;

private:
	float transitionTime;
	
	gef::Sprite splashImage;
};

#endif	//_SPLASH_STATE_H