//@BridgetACasey

#ifndef _MENU_STATE_H
#define _MENU_STATE_H

#pragma once

#include "state.h"
#include "ui/button.h"

//The main menu state, displayed automatically after the splash screen
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
	gef::Sprite backgroundCopy;	//Copy of the background image to create an infinitely scrolling background

	bool play;
};

#endif	//_MENU_STATE_H