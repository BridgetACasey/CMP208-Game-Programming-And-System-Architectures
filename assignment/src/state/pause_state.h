//@BridgetACasey

#pragma once

#include "state.h"

class PauseState : public State
{
protected:
	PauseState(gef::Platform& platform);

public:
	static PauseState* create(gef::Platform& platform);

	void setup() override;

	void onEnter() override;
	void onExit() override;

	void handleInput() override;
	void update(float deltaTime) override;
	void render() override;

private:
};