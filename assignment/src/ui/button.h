//@BridgetACasey

#ifndef _BUTTON_H
#define _BUTTON_H

#pragma once

#include "graphics/sprite.h"
#include "input/game_input.h"

class Button : public gef::Sprite
{
protected:
	Button(GameInput* input_);

public:
	static Button* create(GameInput* input_);

	bool isHovering(bool isMouse);
	bool isClicked(bool isMouse);
	bool isHeld(bool isMouse);

	void setInactiveTexture(gef::Texture* texture);
	void setHoveringTexture(gef::Texture* texture);

	void setSelectedByController(bool selected);
	bool getSelectedByController();

protected:
	GameInput* input;

	gef::Texture* inactive;
	gef::Texture* hovering;

	bool selectedByController;
};

#endif	//_BUTTON_H