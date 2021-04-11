//@BridgetACasey

#pragma once

#include "state.h"
#include "ui/button.h"

class HelpState : public State
{
protected:
	HelpState(gef::Platform& platform);

public:
	static HelpState* create(gef::Platform& platform);

	void setup() override;

	void onEnter() override;
	void onExit() override;

	void handleInput() override;
	bool update(float deltaTime) override;
	void render() override;

	void checkForController();
	void checkButtonStatus(bool usingMouse);

private:
	Button* backButton;

	gef::Sprite background;
	gef::Sprite help;
};