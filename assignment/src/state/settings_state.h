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

private:
	Button* backButton;

	Slider* masterVolumeSlider;
	Slider* musicVolumeSlider;
	Slider* sfxVolumeSlider;

	gef::Sprite background;

	gef::Sprite masterBottomLayer;
	gef::Sprite musicBottomLayer;
	gef::Sprite sfxBottomLayer;

	gef::Sprite masterTopLayer;
	gef::Sprite musicTopLayer;
	gef::Sprite sfxTopLayer;
};