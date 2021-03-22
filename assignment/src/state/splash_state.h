//@BridgetACasey

#pragma once

#include "state.h"

class SplashState : public State
{
protected:
	SplashState(gef::Platform& platform);

public:
	static SplashState* create(gef::Platform& platform);

	void init() override;

	void handleInput() override;
	void update(float deltaTime) override;
	void render() override;

	void onEnter() override;
	void onExit() override;

private:
};