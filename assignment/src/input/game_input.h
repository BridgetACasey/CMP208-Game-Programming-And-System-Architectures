//@BridgetACasey

#ifndef _GAME_INPUT_H
#define _GAME_INPUT_H

#pragma once

#include <input/input_manager.h>
#include <input/touch_input_manager.h>
#include <input/sony_controller_input_manager.h>
#include <maths/vector2.h>
#include <input/keyboard.h>
#include <system/platform.h>

#include "move_command.h"

class InputCommand;
class GameObject;

enum class ControllerCode	//A more readable way of checking which angle the controller's analog sticks are sitting at
{
	NONE = 0,
	UP,
	LEFT,
	DOWN,
	RIGHT
};

enum class MouseCode
{
	NONE = 0,
	PRESSED,
	HELD,
	RELEASED
};

struct Controller
{
	ControllerCode leftStick = ControllerCode::NONE;
	ControllerCode rightStick = ControllerCode::NONE;

	gef::Vector2 leftPosition;
	gef::Vector2 rightPosition;

	bool active;	//To check if the controller is being actively used, if not, it is assumed mouse & keyboard are being used
};

struct Mouse
{
	MouseCode left = MouseCode::NONE;
	MouseCode right = MouseCode::NONE;

	gef::Vector2 position;
};

struct Key	//A key that is assigned to a specific command, so that it can be easily modified
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

	ControllerCode processControllerCodes(gef::Vector2& position);
	void processMouseButtonInput(Int32 touchID, gef::TouchType type);
	void processTouchInput();

	const gef::SonyController* getSonyController();
	Controller* getController();
	Mouse* getMouse();
	gef::Keyboard* getKeyboard();

private:
	Key* assignKeys();

	gef::InputManager* inputManager;

	Controller* controller;
	Mouse* mouse;

	JumpCommand jump;
	MoveLeftCommand left;
	MoveRightCommand right;
	SprintCommand sprint;

	Key* keyMoveLeft;
	Key* keyMoveRight;
	Key* keyJump;
	Key* keySprint;

	Int32 active_touch_id_;
};

#endif	//_GAME_INPUT_H