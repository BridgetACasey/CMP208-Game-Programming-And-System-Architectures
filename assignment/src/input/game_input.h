//@BridgetACasey

#ifndef _GAME_INPUT_H
#define _GAME_INPUT_H

#pragma once

#include "input/input_manager.h"
#include "input/touch_input_manager.h"
#include "maths/vector2.h"

class GameInput
{
protected:
	GameInput();

public:
	~GameInput();

	static GameInput* create(gef::InputManager* inputManager_);

	void update();

	inline const gef::Vector2& getMousePosition();

private:
	gef::InputManager* inputManager;
};

#endif