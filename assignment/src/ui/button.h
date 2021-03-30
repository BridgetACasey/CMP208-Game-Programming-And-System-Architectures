//@BridgetACasey

#pragma once

#include "graphics/sprite.h"
#include "input/game_input.h"

class Button : public gef::Sprite
{
protected:
	Button(GameInput* input_);

public:
	static Button* create(GameInput* input_);

	bool isHovering();
	bool isClicked();
	bool isHeld();

	void setInactiveTexture(gef::Texture* texture);
	void setHoveringTexture(gef::Texture* texture);

protected:
	GameInput* input;

	gef::Texture* inactive;
	gef::Texture* hovering;
};