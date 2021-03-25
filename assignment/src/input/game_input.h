//@BridgetACasey

#ifndef _GAME_INPUT_H
#define _GAME_INPUT_H

#pragma once

#include <input/input_manager.h>
#include <input/touch_input_manager.h>
#include <maths/vector2.h>
#include <input/keyboard.h>
#include <system/platform.h>

#include "jump_command.h"
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
	std::string keyText;
};

class GameInput
{
protected:
	GameInput(gef::Platform& platform, gef::InputManager* inputManager_);

public:
	~GameInput();

	static GameInput* create(gef::Platform& platform, gef::InputManager* inputManager_);

	void update(GameObject* gameObject);

	void bindKeys();
	void processKeyCommands(GameObject* gameObject);
	void processMouseButton(Int32 touchID, gef::TouchType type);

	void processTouchInput();

	Mouse* getMouse();

	gef::Vector2& getMousePosition();

private:
	Key* assignKeys();

	gef::InputManager* inputManager;

	Mouse* mouse;

	Key* key_a;
	Key* key_d;
	Key* key_space;

	JumpCommand jump;
	MoveCommand left;
	MoveCommand right;

	Int32 active_touch_id_;
	gef::Vector2 touch_position_;
};

#endif