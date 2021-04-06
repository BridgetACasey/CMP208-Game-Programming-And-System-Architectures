//@BridgetACasey

#ifndef _GAME_INPUT_H
#define _GAME_INPUT_H

#pragma once

#include <input/input_manager.h>
#include <input/touch_input_manager.h>
#include <maths/vector2.h>
#include <input/keyboard.h>
#include <system/platform.h>

#include "move_command.h"

class InputCommand;
class GameObject;

enum class MouseCode
{
	NONE = 0,
	PRESSED,
	HELD,
	RELEASED
};

struct Mouse
{
	MouseCode left = MouseCode::NONE;
	MouseCode right = MouseCode::NONE;
	gef::Vector2 position;
};

struct Key
{
	InputCommand* command;
};

class GameInput
{
protected:
	GameInput(gef::Platform& platform);

public:
	~GameInput();

	static GameInput* create(gef::Platform& platform);

	void update();
	void processGameObjectCommands(GameObject* gameObject);

	void bindKeys();

	void processMouseButton(Int32 touchID, gef::TouchType type);
	void processTouchInput();

	Mouse* getMouse();
	gef::Keyboard* getKeyboard();

private:
	Key* assignKeys();

	gef::InputManager* inputManager;

	Mouse* mouse;

	JumpCommand jump;
	MoveLeftCommand left;
	MoveRightCommand right;
	SprintCommand sprint;

	Key* key_a;
	Key* key_d;
	Key* key_space;
	Key* key_l_shift;

	Int32 active_touch_id_;
};

#endif