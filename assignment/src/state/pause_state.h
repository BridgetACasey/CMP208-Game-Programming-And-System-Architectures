//@BridgetACasey

#pragma once

#include "state.h"
#include "ui/button.h"

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
	bool update(float deltaTime) override;
	void render() override;

	void checkForController();
	void checkButtonStatus(bool usingMouse);

private:
	int buttonIndex;

	Button* buttons[2];

	gef::Sprite background;
};