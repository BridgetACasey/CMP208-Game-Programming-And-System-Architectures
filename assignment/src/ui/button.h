//@BridgetACasey

#pragma once

#include "graphics/sprite.h"
#include "input/game_input.h"

class Button : gef::Sprite
{
protected:
	Button(GameInput* input_);

public:
	static Button* create(GameInput* input_);

	bool isHovering();
	bool isClicked();

private:
	GameInput* input;
};