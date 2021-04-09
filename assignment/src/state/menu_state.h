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

	void checkForController();
	void checkButtonStatus(bool usingMouse);

	void updateBackground(float deltaTime);

private:
	int buttonIndex;
	
	float scrollSpeed;

	Button* buttons[4];

	gef::Sprite title;

	gef::Sprite background;
	gef::Sprite backgroundCopy;

	bool play;
};