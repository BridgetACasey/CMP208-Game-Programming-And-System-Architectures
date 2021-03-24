//@BridgetACasey

#pragma once

#include "state.h"

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
	void update(float deltaTime) override;
	void render() override;

private:
	float transitionTime = 0.0f;
};