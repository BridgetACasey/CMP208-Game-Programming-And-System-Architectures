//@BridgetACasey

#ifndef _BUTTON_H
#define _BUTTON_H

#pragma once

#include "maths/vector2.h"
#include "input/game_input.h"

class Button
{
protected:
	Button();

public:
	static Button* Create();

	bool isHovering();
	bool isClicked();

	void SetPosition(float x, float y);
	void SetScale(float x, float y);

	gef::Vector2* getPosition();
	gef::Vector2* getScale();

private:
	gef::Vector2 position;
	gef::Vector2 scale;

	GameInput* input;
};

#endif