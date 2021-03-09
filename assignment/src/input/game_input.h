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

	inline const gef::Vector2& getMousePosition();

private:
	Key* assignKeys();

	gef::InputManager* inputManager;

	Key* key_a;
	Key* key_d;
	Key* key_space;

	JumpCommand jump;
	MoveCommand left;
	MoveCommand right;
};

#endif