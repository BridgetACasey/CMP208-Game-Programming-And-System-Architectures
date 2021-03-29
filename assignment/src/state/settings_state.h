//@BridgetACasey

#pragma once

#include "state.h"
#include "ui/button.h"

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

	gef::Sprite background;
};