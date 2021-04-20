//@BridgetACasey

#include "game_input.h"
#include <iostream>

GameInput::GameInput(gef::Platform& platform)
{
	inputManager = gef::InputManager::Create(platform);

	// make sure if there is a panel to detect touch input, then activate it
	if (inputManager && inputManager->touch_manager() && (inputManager->touch_manager()->max_num_panels() > 0))
	{
		inputManager->touch_manager()->EnablePanel(0);
	}

	active_touch_id_ = -1;

	controller = new Controller();
	mouse = new Mouse();
	
	keyJump = new Key();
	keyMoveLeft = new Key();
	keyMoveRight = new Key();
	keySprint = new Key();

	bindKeys();
}

GameInput::~GameInput()
{

}

GameInput* GameInput::create(gef::Platform& platform)
{
	return new GameInput(platform);
}

void GameInput::update()
{
	if (inputManager)
	{
		inputManager->Update();

		if (controller)
		{
			if (getSonyController()->buttons_pressed())	//If any buttons have been pressed, assume the controller is the active input device
			{
				controller->active = true;
			}

			controller->leftPosition = gef::Vector2(inputManager->controller_input()->GetController(0)->left_stick_x_axis(),
				inputManager->controller_input()->GetController(0)->left_stick_y_axis());
			controller->rightPosition = gef::Vector2(inputManager->controller_input()->GetController(0)->right_stick_x_axis(),
				inputManager->controller_input()->GetController(0)->right_stick_y_axis());

			controller->leftStick = processControllerCodes(controller->leftPosition);
			controller->rightStick = processControllerCodes(controller->rightPosition);
		}

		if (mouse)
		{
			mouse->position = inputManager->touch_manager()->mouse_position();
		}

		processTouchInput();
	}
}

void GameInput::processGameObjectCommands(GameObject* gameObject)
{
	Key* key = assignKeys();

	//Commands are executed upon a GameObject, rather than being bound to the Player class, for example
	//This means it would be easy to switch between controlling a Player and controlling another GameObject

	if (key)
	{
		key->command->executeObjectCommand(gameObject);
	}
}

void GameInput::bindKeys()
{
	/*
	* Assigning keys to their respective commands.
	* Setting up input this way means it is easier to alter which buttons or keyboard keys execute which commands.
	* This system would also make it easier to change key bindings at run time.
	*/

	keyJump->command = &jump;
	keyMoveLeft->command = &left;
	keyMoveRight->command = &right;
	keySprint->command = &sprint;
}

ControllerCode GameInput::processControllerCodes(gef::Vector2& position)
{
	ControllerCode code = ControllerCode::NONE;

	//Checks if analog sticks are being moved, and assigns the corresponding direction

	if (position.x <= -0.9f)
	{
		code = ControllerCode::LEFT;
		controller->active = true;
	}

	else if (position.x >= 0.9f)
	{
		code = ControllerCode::RIGHT;
		controller->active = true;
	}

	else if (position.y <= -0.9f)
	{
		code = ControllerCode::UP;
		controller->active = true;
	}

	else if (position.y >= 0.9f)
	{
		code = ControllerCode::DOWN;
		controller->active = true;
	}

	return code;
}

void GameInput::processMouseButtonInput(Int32 touchID, gef::TouchType type)
{
	MouseCode button;

	//Translates TouchType enum values to MouseCode values
	//Not entirely necessary, but is more readable when utilising the mouse
	//Also sets the mouse to the active input device

	switch (type)
	{
		case gef::TouchType::TT_NEW:
			button = MouseCode::PRESSED;
			controller->active = false;
			break;

		case gef::TouchType::TT_ACTIVE:
			button = MouseCode::HELD;
			controller->active = false;
			break;

		case gef::TouchType::TT_RELEASED:
			button = MouseCode::RELEASED;
			controller->active = false;
			break;

		default:
			button = MouseCode::NONE;
	}

	//Determines which mouse button has been pressed
	if (touchID == 0)
	{
		mouse->left = button;
	}

	if (touchID == 1)
	{
		mouse->right = button;
	}
}

Key* GameInput::assignKeys()
{
	//Returns the respective command key based on what button or key has been pressed

	if (inputManager->keyboard()->IsKeyDown(gef::Keyboard::KeyCode::KC_SPACE) || getSonyController()->buttons_down() == gef_SONY_CTRL_CROSS)
	{
		return keyJump;
	}

	if (inputManager->keyboard()->IsKeyDown(gef::Keyboard::KeyCode::KC_A) || controller->leftStick == ControllerCode::LEFT)
	{
		return keyMoveLeft;
	}

	if (inputManager->keyboard()->IsKeyDown(gef::Keyboard::KeyCode::KC_D) || controller->leftStick == ControllerCode::RIGHT)
	{
		return keyMoveRight;
	}

	if (inputManager->keyboard()->IsKeyDown(gef::Keyboard::KeyCode::KC_LSHIFT) || getSonyController()->buttons_down() == gef_SONY_CTRL_CIRCLE)
	{
		return keySprint;
	}

	return nullptr;
}

void GameInput::processTouchInput()
{
	const gef::TouchInputManager* touch_input = inputManager->touch_manager();

	if (touch_input && (touch_input->max_num_panels() > 0))
	{
		// get the active touches for this panel
		const gef::TouchContainer& panel_touches = touch_input->touches(0);

		// go through the touches
		for (gef::ConstTouchIterator touch = panel_touches.begin(); touch != panel_touches.end(); ++touch)
		{
			// if active touch id is -1, then we are not currently processing a touch
			if (active_touch_id_ == -1)
			{
				// check for the start of a new touch
				if (touch->type == gef::TT_NEW)
				{
					active_touch_id_ = touch->id;

					// do any processing for a new touch here
					// we're just going to record the position of the touch
					processMouseButtonInput(touch->id, touch->type);
				}
			}
			else if (active_touch_id_ == touch->id)
			{
				// we are processing touch data with a matching id to the one we are looking for
				if (touch->type == gef::TT_ACTIVE)
				{
					// update an active touch here
					// we're just going to record the position of the touch
					processMouseButtonInput(touch->id, touch->type);
				}
				else if (touch->type == gef::TT_RELEASED)
				{
					// the touch we are tracking has been released
					// perform any actions that need to happen when a touch is released here
					// we're not doing anything here apart from resetting the active touch id
					processMouseButtonInput(touch->id, touch->type);

					active_touch_id_ = -1;
				}
			}
		}
	}
}

const gef::SonyController* GameInput::getSonyController()
{
	return inputManager->controller_input()->GetController(0);
}

Controller* GameInput::getController()
{
	return controller;
}

Mouse* GameInput::getMouse()
{
	return mouse;
}

gef::Keyboard* GameInput::getKeyboard()
{
	return inputManager->keyboard();
}