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

	void setInactiveColour(UInt32 inactiveColour_);
	void setHoveringColour(UInt32 hoveringColour_);
	void setClickedColour(UInt32 clickedColour_);

private:
	GameInput* input;

	UInt32 inactiveColour;
	UInt32 hoveringColour;
	UInt32 clickedColour;
};