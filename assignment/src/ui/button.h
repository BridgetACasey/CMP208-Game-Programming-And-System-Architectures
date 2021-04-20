//@BridgetACasey

#ifndef _BUTTON_H
#define _BUTTON_H

#pragma once

#include "graphics/sprite.h"
#include "input/game_input.h"

//A button object that can be clicked on
class Button : public gef::Sprite
{
protected:
	Button(GameInput* input);

public:
	static Button* create(GameInput* input);

	bool isHovering(bool isMouse);
	bool isClicked(bool isMouse);
	bool isHeld(bool isMouse);

	void setInactiveTexture(gef::Texture* texture);
	void setHoveringTexture(gef::Texture* texture);

	void setSelectedByController(bool selected);
	bool getSelectedByController();

protected:
	GameInput* gameInput;

	gef::Texture* inactive;
	gef::Texture* hovering;

	bool selectedByController;	//For checking if this is the active button being interacted with by the Sony Controller
};

#endif	//_BUTTON_H