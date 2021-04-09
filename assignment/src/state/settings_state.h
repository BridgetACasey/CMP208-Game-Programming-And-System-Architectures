//@BridgetACasey

#pragma once

#include "state.h"
#include "ui/slider.h"

class SettingsState : public State
{
protected:
	SettingsState(gef::Platform& platform);

public:
	static SettingsState* create(gef::Platform& platform);

	void setup() override;

	void onEnter() override;
	void onExit() override;

	void handleInput() override;
	bool update(float deltaTime) override;
	void render() override;

	void checkForController();
	void checkButtonStatus(float deltaTime, bool usingMouse);

private:
	int buttonIndex;

	Button* buttons[6];
	
	Button* backButton;

	Slider* masterVolumeSlider;
	Slider* musicVolumeSlider;
	Slider* sfxVolumeSlider;

	Slider* speedSlider;
	Slider* jumpSlider;

	gef::Sprite background;
};