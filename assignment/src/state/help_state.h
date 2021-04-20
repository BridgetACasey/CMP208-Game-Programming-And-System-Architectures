//@BridgetACasey

#ifndef _HELP_STATE_H
#define _HELP_STATE_H

#pragma once

#include "state.h"
#include "ui/button.h"

//The screen that informs the player of how to play the game
//Does nothing except display an image
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

#endif	//_HELP_STATE_H