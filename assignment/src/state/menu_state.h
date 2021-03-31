//@BridgetACasey

#pragma once

#include "state.h"
#include "ui/button.h"

class MenuState : public State
{
protected:
	MenuState(gef::Platform& platform);

public:
	static MenuState* create(gef::Platform& platform);

	void setup() override;

	void onEnter() override;
	void onExit() override;

	void handleInput() override;
	bool update(float deltaTime) override;
	void render() override;

	void updateBackground(float deltaTime);

private:
	Button* playButton;
	Button* settingsButton;
	Button* helpButton;
	Button* exitButton;

	Int32 music;

	gef::Sprite background;
	gef::Sprite backgroundCopy;

	bool play;
};