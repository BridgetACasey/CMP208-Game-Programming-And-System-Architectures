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

	void init() override;

	void handleInput() override;
	void update(float deltaTime) override;
	void render() override;

	void onEnter() override;
	void onExit() override;

private:
	Button* playButton;
	Button* settingsButton;
	Button* helpButton;
	Button* exitButton;
};