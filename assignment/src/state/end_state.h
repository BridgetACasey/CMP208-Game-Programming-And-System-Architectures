//@BridgetACasey

#ifndef _END_STATE_H
#define _END_STATE_H

#pragma once

#include "state.h"
#include "ui/button.h"

//The state displayed once the player has completed the level or died
class EndState : public State
{
protected:
	EndState(gef::Platform& platform);

public:
	static EndState* create(gef::Platform& platform);

	void setup() override;

	void onEnter() override;
	void onExit() override;

	void handleInput() override;
	bool update(float deltaTime) override;
	void render() override;

	void checkForController();
	void checkButtonStatus(bool usingMouse);

	void setLastScore(int score);

private:
	int lastScore;
	int highestScore;

	int buttonIndex;

	char* text;

	Button* buttons[2];

	gef::Sprite background;

	bool play;
};

#endif	//_END_STATE_H